// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/CommandLine.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_COMMANDLINE_H_INCLUDED)
#define MKX_COMMANDLINE_H_INCLUDED


#include "Mkx/CommandLine/Configuration.h"
#include "Mkx/CommandLine/Argument.h"
#include "Mkx/CommandLine/ArgumentList.h"


/**
 * @brief Parse an argument list from command line arguments.
 * @param numberOfArguments The number of arguments.
 * @param arguments The arguments.
 * @return The argument list on success, a null pointer on failure.
 */
Mkx_CommandLine_ArgumentList*
Mkx_CommandLine_ArgumentList_parse
  (
    int argc,
    const char** argv
  );

#endif // MKX_COMMANDLINE_H_INCLUDED
