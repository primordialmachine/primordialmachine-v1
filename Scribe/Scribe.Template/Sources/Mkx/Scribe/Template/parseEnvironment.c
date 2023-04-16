// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/parseEnvironment.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/parseEnvironment.h"


#include "Mkx/Scribe/Environment.h"
#include "Mkx/Scribe/Template/EvaluateNode.h"


Mkx_Scribe_Environment*
Mkx_Template_parseEnvironment
  (
    Mkx_SymbolScanner *symbolScanner
  )
{
  Mkx_Template_EnvironmentScanner* environmentScanner = Mkx_Template_EnvironmentScanner_create(symbolScanner);
  Mkx_Template_EnvironmentParser* environmentParser = Mkx_Template_EnvironmentParser_create(environmentScanner);
  Mkx_Scribe_Hll_Node* createTableNode = Mkx_Template_EnvironmentParser_run(environmentParser);
  Mkx_Template_evaluateNode(createTableNode, NULL);
  Mkx_Scribe_Environment* environment = Ring1_cast(Mkx_Scribe_Environment*, Mkx_Interpreter_Stack_getObjectAt(Ring2_Context_get(), 0));
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
  return environment;
}
