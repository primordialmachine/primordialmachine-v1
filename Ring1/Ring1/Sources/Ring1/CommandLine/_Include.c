// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/CommandLine/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/CommandLine/_Include.h"

#include "Ring1/CommandLine/ArgumentParser.h"


Ring1_NoDiscardReturn() Ring1_CommandLine_ArgumentList*
Ring1_CommandLine_ArgumentList_parse
  (
    int argc,
    char const** argv
  )
{
  Ring1_CommandLine_ArgumentList* argumentList = NULL;
  if (Ring1_CommandLine_ArgumentList_create(&argumentList)) {
    return NULL;
  }
  for (int argi = 1; argi < argc; ++argi) {
    Ring1_CommandLine_ArgumentParser argumentParser;
    argumentParser.start = argv[argi];
    argumentParser.current = argv[argi];
    Ring1_CommandLine_Argument* argument = NULL;
    if (Ring1_CommandLine_ArgumentParser_parse(&argument, &argumentParser)) {
      Ring1_CommandLine_ArgumentList_unref(argumentList);
      return NULL;  
    }
    if (Ring1_CommandLine_ArgumentList_append(argumentList, argument)) {
      Ring1_CommandLine_Argument_unref(argument);
      Ring1_CommandLine_ArgumentList_unref(argumentList);
      return NULL;
    }
    Ring1_CommandLine_Argument_unref(argument);
  }
  return argumentList;
}
