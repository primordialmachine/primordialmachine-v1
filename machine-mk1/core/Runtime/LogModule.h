// @file Runtime/LogModule.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_LOGMODULE_H_INCLUDED)
#define MACHINE_RUNTIME_LOGMODULE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Configuration.h"
#include "Runtime/Status.h"

#if defined(MACHINE_WITH_LOG) && 1 == MACHINE_WITH_LOG

Machine_StatusValue Machine_initializeLogModule();

void Machine_uninitializeLogModule();

/// @brief To error log.
#define Machine_LogFlags_ToErrors (4)

/// @brief To warnings log.
#define Machine_LogFlags_ToWarnings (2)

/// @brief to informations log.
#define Machine_LogFlags_ToInformations (1)

/// @brief Write a log message.
/// @param flags Bitwise or of Machine_LogFlags_* constants.
/// @param file, line The file name and the line in that file in the C-level source as specified by __FILE__ and __LINE__, respectively.
/// @param format, ... The printf-style format string and format arguments.
void Machine_log(int flags, const char* file, int line, const char* format, ...);

#endif // MACHINE_WITH_LOG

#endif // MACHINE_RUNTIME_LOGMODULE_H_INCLUDED
