#include "Mkx/Scribe/SafeExecute.h"

#include "Ring2/Operations.h"
#include "Mkx/Scribe/Cas/Tool.h"
#include "Mkx/Scribe/Template/Tool.h"

#include <stdlib.h>
#include <stdio.h>


Ring1_NoReturn() static void
invalidCommandLineError
  (
    Ring2_Context* context
  )
{
  fprintf(stderr, "invalid command-line arguments\n");
  fprintf(stderr, "usage:\n" "<program> [tool name] [tool arguments]\n");
  Ring1_Status_set(Ring1_Status_InvalidArgument);
  Ring2_jump();
}

Ring1_NoReturn() static void
tooFewArgumentsCommandLineError
  (
    Ring2_Context* context
  )
{
  fprintf(stderr, "no tool name specified\n");
  fprintf(stderr, "usage:\n" "<program> [tool name] [tool arguments]\n");
  Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
  Ring2_jump();
}

Ring1_NoReturn() static void
invalidToolNameCommandLineError
  (
    Ring2_Context* context
  )
{
  fprintf(stderr, "invalid tool name specified\n");
  fprintf(stderr, "usage:\n" "<program> [tool name] [tool arguments]\n");
  Ring1_Status_set(Ring1_Status_InvalidArgument);
  Ring2_jump();
}

Ring1_NoReturn() static void
unknownToolCommandLineError
  (
    Ring2_Context* context
  )
{
  fprintf(stderr, "unknown tool specified\n");
  fprintf(stderr, "usage:\n" "<program> [tool name] [tool arguments]\n");
  Ring1_Status_set(Ring1_Status_InvalidArgument);
  Ring2_jump();
}

Ring1_CheckReturn() int
Scribe_safeExecute
  (
    Ring2_Context* context,
    int numberOfArguments,
    const char** arguments
  )
{
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment))
  {
    Ring2_CommandLine_ArgumentList* argumentList = Ring2_CommandLine_ArgumentList_create(numberOfArguments, arguments);

    if (!argumentList) {
      invalidCommandLineError(context);
    }

    if (Ring2_CommandLine_ArgumentList_getSize(argumentList) < 1) {
      tooFewArgumentsCommandLineError(context);
    }

    // Get an remove the argument denoting the tool to execute.
    Ring2_CommandLine_Argument* argument = Ring2_CommandLine_ArgumentList_getAt(argumentList, 0);
    Ring2_CommandLine_ArgumentList_removeAt(argumentList, 0);
    Ring2_String* toolName = Ring2_CommandLine_Argument_getValue(argument);
    if (!toolName) {
      invalidToolNameCommandLineError(context);
    }

    void (*function)(Ring2_Context * context, Ring2_CommandLine_ArgumentList * argumentList) = NULL;
    if (Ring2_String_isEqualTo(context, toolName, Ring2_String_fromC(false, "template")))
    {
      function = &Scribe_Template_main;
    }
    else if (Ring2_String_isEqualTo(context, toolName, Ring2_String_fromC(false, "cas")))
    {
      function = &Scribe_Cas_main;
    }
    else
    {
      unknownToolCommandLineError(context);
    }

    (*function)(context, argumentList);

    Ring2_popJumpTarget();
    return 0;
  }
  else
  {
    Ring2_popJumpTarget();
    return 1;
  }
}
