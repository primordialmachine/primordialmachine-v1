// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Log.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LOG_H_INCLUDED)
#define RING2_LOG_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Log.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"
#include "Ring1/Module.h"

Ring1_Module_Declare(Ring2, LogModule)

/// @brief To error log.
#define Ring2_LogFlags_ToErrors (4)

/// @brief To warnings log.
#define Ring2_LogFlags_ToWarnings (2)

/// @brief to informations log.
#define Ring2_LogFlags_ToInformations (1)

/// @brief Write a log message.
/// @param flags Bitwise or of Machine_LogFlags_* constants.
/// @param file, line The file name and the line in that file in the C-level source as specified by __FILE__ and __LINE__, respectively.
/// @param format, ... The printf-style format string and format arguments.
void
Ring2_log
  (
    int flags,
    const char* file,
    int line,
    const char* format,
    ...
  );

#endif // RING2_LOG_H_INCLUDED
