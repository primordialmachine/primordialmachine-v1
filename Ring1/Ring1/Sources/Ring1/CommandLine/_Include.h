// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/CommandLine/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_COMMANDLINE__INCLUDE_H_INCLUDED)
#define RING1_COMMANDLINE__INCLUDE_H_INCLUDED

#include "Ring1/CommandLine/Configuration.h"
#include "Ring1/CommandLine/Argument.h"
#include "Ring1/CommandLine/ArgumentList.h"


/// @brief Parse an argument list from command line arguments.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
/// @return The argument list on success, a null pointer on failure.
Ring1_NoDiscardReturn() Ring1_CommandLine_ArgumentList*
Ring1_CommandLine_ArgumentList_parse
  (
    int argc,
    char const** argv
  );


#endif // RING1_COMMANDLINE__INCLUDE_H_INCLUDED
