// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/CommandLine.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/CommandLine.h"

#include "Mkx/CommandLine/Parser.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Mkx_CommandLine_ArgumentList*
Mkx_CommandLine_ArgumentList_parse
  (
    int argc,
    const char** argv
  )
{
  Mkx_CommandLine_ArgumentList* argumentList = NULL;
  if (Mkx_CommandLine_ArgumentList_create(&argumentList)) {
    return NULL;
  }
  for (int argi = 1; argi < argc; ++argi)
  {
    Mkx_CommandLine_Implementation_ArgumentParser argumentParser;
    argumentParser.start = argv[argi];
    argumentParser.current = argv[argi];
    Mkx_CommandLine_Argument* argument = NULL;
    if (Mkx_CommandLine_Implementation_ArgumentParser_parse(&argument,
                                                            &argumentParser)) {
      Mkx_CommandLine_ArgumentList_unref(argumentList);
      return NULL;  
    }
    if (Mkx_CommandLine_ArgumentList_append(argumentList, argument))
    {
      Mkx_CommandLine_Argument_unref(argument);
      Mkx_CommandLine_ArgumentList_unref(argumentList);
      return NULL;
    }
    Mkx_CommandLine_Argument_unref(argument);
  }
  return argumentList;
}
