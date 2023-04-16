// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/CommandLine/ArgumentParser.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_COMMANDLINE_ARGUMENTPARSER_H_INCLUDED)
#define RING1_COMMANDLINE_ARGUMENTPARSER_H_INCLUDED

#include "Ring1/CommandLine/_Include.h"


typedef struct Ring1_CommandLine_ArgumentParser {
  char const* start;
  char const* current;
} Ring1_CommandLine_ArgumentParser;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_CommandLine_ArgumentParser_parse
  (
    Ring1_CommandLine_Argument **result,
    Ring1_CommandLine_ArgumentParser* parser
  );


#endif // RING1_COMMANDLINE_ARGUMENTPARSER_H_INCLUDED
