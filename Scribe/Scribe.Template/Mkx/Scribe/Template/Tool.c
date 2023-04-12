// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/Tool.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/Tool.h"


#include "Mkx/Scribe/Common.h"
#include "Mkx/Scribe/Environment/Environment.h"
#include "Mkx/Scribe/Environment/Variable.h"
#include "Mkx/Scribe/Template/EvaluateNode.h"
#include "Mkx/Scribe/Template/parseEnvironment.h"
#include "Mkx/Scribe/Template/parseAndEvalTemplate.h"
#include "Mkx/Scribe/Template/Library.h"
#include "Mkx/Scribe/Hll.h"
#include "Mkx/Scribe/Template/parseExpression.h"
#include <stdio.h>


void
Scribe_Template_main
  (
    Ring2_Context* context,
    Ring2_CommandLine_ArgumentList *argumentList
  )
{
  Mkx_Scribe_Environment* rootEnv = Mkx_Scribe_Environment_create(context);
  // Validate the argument list.
  if (Ring2_CommandLine_ArgumentList_getSize(argumentList) < 3)
  {
    fprintf(stderr, "too few arguments\n");
    fprintf(stderr, "usage:\n" "<program> template [variables] configuration source target\n");
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }

  // Load the configuration file.
  Ring2_String* configuration_pathname = Ring2_CommandLine_Argument_getValue(Ring2_CommandLine_ArgumentList_getAt(argumentList, Ring2_CommandLine_ArgumentList_getSize(argumentList) - 3));
  Ring2_emitf(context, Ring2_String_fromC(false, "  configuration pathname: %s\n"), configuration_pathname);
  Ring2_String* configuration_file =
    Machine_getFileContentsAsString(configuration_pathname);
  Mkx_Scribe_Environment* parsedEnv =
    Mkx_Template_parseEnvironment(Mkx_SymbolScanner_create(configuration_file, configuration_pathname));
  Mkx_Scribe_Environment_setAll(rootEnv, parsedEnv);

  Mkx_Scribe_Template_Library_register(rootEnv);

  for (int64_t i = 0; i < Ring2_CommandLine_ArgumentList_getSize(argumentList) - 3; ++i)
  {
    Ring2_CommandLine_Argument* argument = Ring2_CommandLine_ArgumentList_getAt(argumentList, i);
    Ring2_String *name = Ring2_CommandLine_Argument_getName(argument),
                 *value = Ring2_CommandLine_Argument_getValue(argument);
    if (!name || !value) {
      fprintf(stderr, "invalid command-line arguments\n");
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    Mkx_Scribe_Variable* var = Mkx_Scribe_Variable_create(name);
    {
      Ring2_String* filename = Ring2_String_printf(context, Ring2_String_fromC(false, "`%s` = `%s`"), name, value);
      Mkx_SymbolScanner* symbolScanner = Mkx_SymbolScanner_create(value, filename);
      Mkx_Scribe_Hll_Node* node = Mkx_Template_parseExpression(symbolScanner);
      Mkx_Template_evaluateNode(node, NULL);
      if (Mkx_Interpreter_Stack_getSize(context) != 1) { 
        Ring2_emitf(context, Ring2_String_fromC(false, "%s: number of stack values %i\n"), name, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()));
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      if (!Mkx_Interpreter_Stack_isStringAt(context, 0) && !Mkx_Interpreter_Stack_isIntegerAt(context, 0)) {
        Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s: value neither a string nor an integer\n"), name);
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      Ring2_Value*value = Mkx_Interpreter_Stack_getAt(context, 0);
      Mkx_Scribe_Variable_set(var, *value);
      Mkx_Interpreter_Stack_pop(context, 1);
    }
    Mkx_Scribe_Environment_set(rootEnv, var);
  }

  
  Ring2_String* sourcePathname = Ring2_CommandLine_Argument_getValue(Ring2_CommandLine_ArgumentList_getAt(argumentList,
                                                                                                          Ring2_CommandLine_ArgumentList_getSize(argumentList) - 2)),
              * targetPathname = Ring2_CommandLine_Argument_getValue(Ring2_CommandLine_ArgumentList_getAt(argumentList,
                                                                                                          Ring2_CommandLine_ArgumentList_getSize(argumentList) - 1));
  
  Mkx_Scribe_Hll_Node *taskNode = Mkx_Scribe_Hll_Node_createTask(NULL);
  Mkx_Scribe_Hll_Node *sourcePathnameNode = Mkx_Scribe_Hll_Node_createStringLiteral(NULL, sourcePathname),
                      *targetPathnameNode = Mkx_Scribe_Hll_Node_createStringLiteral(NULL, targetPathname);
  Mkx_Scribe_Hll_Node_append(taskNode, sourcePathnameNode);
  Mkx_Scribe_Hll_Node_append(taskNode, targetPathnameNode);

  Mkx_Template_evaluateNode(taskNode, rootEnv);
}
