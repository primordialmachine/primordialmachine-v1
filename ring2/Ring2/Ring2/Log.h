// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Log.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LOG_H_INCLUDED)
#define RING2_LOG_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

Ring1_CheckReturn() Ring1_Result
Ring2_LogModule_startup
  (
  );

void
Ring2_LogModule_shutdown
  (
  );

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
