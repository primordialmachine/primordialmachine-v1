// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_H_INCLUDED)
#define RING1_LOG_H_INCLUDED

#include "Ring1/Log/Configuration.h"
#include "Ring1/Module.h"
#include <stdarg.h>


Ring1_Module_Declare(Ring1, Log)


/// @internal
/// @brief The information log level is used for informations.
/// @remark This log level is enabled in debug and release mode.
#define Ring1_Log_Level_Information (0)

/// @internal
/// @brief The warning log level is used for warnings.
/// @remark This log level is enabled in debug and release mode.
#define Ring1_Log_Level_Warning (1)

/// @internal
/// @brief The warning log level is used for warnings.
/// @remark This log level is enabled in debug and release mode.
#define Ring1_Log_Level_Error (2)

/// @internal
/// @brief Function for loggin an error.
/// @param level The log level.
/// @param file, line The file name and the line number the message pertains to
/// as provided by __FILE__ and __LINE__.
/// @param format A printf-style format string.
/// @param arguments The printf-style argument list.
void
Ring1_log_fv
  (
    int level,
    const char* file,
    int line,
    const char* format,
    va_list args
  );

/// @internal
/// @brief Function for loggin an error.
/// @param level The log level.
/// @param file, line The file name and the line number the message pertains to
/// as provided by __FILE__ and __LINE__.
/// @param format A printf-style format string.
/// @param ... A printf-style list of arguments.
void
Ring1_log_f
  (
    int level,
    const char* file,
    int line,
    const char* format,
    ...
  );

/// @internal
/// @brief Macro logging an information message.
/// @param format, A printf-style format string.
/// @param ... A printf-style list of arguments.
#define Ring1_Log_information(...) \
  Ring1_log_f(Ring1_Log_Level_Information, __FILE__, __LINE__, __VA_ARGS__)

/// @internal
/// @brief Macro logging a warning message.
/// @param format, A printf-style format string.
/// @param ... A printf-style list of arguments.
#define Ring1_Log_warning(...) \
  Ring1_log_f(Ring1_Log_Level_Warning, __FILE__, __LINE__, __VA_ARGS__)

/// @internal
/// @brief Macro logging an error message.
/// @param format, A printf-style format string.
/// @param ... A printf-style list of arguments.
#define Ring1_Log_error(...) \
  Ring1_log_f(Ring1_Log_Level_Error, __FILE__, __LINE__, __VA_ARGS__)


#endif  // RING1_LOG_H_INCLUDED
