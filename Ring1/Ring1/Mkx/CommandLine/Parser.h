// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/CommandLine/Parser.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_COMMANDLINE_PARSER_H_INCLUDED)
#define MKX_COMMANDLINE_PARSER_H_INCLUDED

#include "Mkx/CommandLine.h"

typedef struct Mkx_CommandLine_Implementation_ArgumentParser
{
  const char* start;
  const char* current;
} Mkx_CommandLine_Implementation_ArgumentParser;

Ring1_Result
Mkx_CommandLine_Implementation_ArgumentParser_parse
  (
    Mkx_CommandLine_Argument **result,
    Mkx_CommandLine_Implementation_ArgumentParser* parser
  );

#endif // MKX_COMMANDLINE_PARSER_H_INCLUDED
