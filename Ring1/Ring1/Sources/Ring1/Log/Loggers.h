// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Loggers.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_LOGGERS_H_INCLUDED)
#define RING1_LOG_LOGGERS_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/Loggers.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Log/ConsoleLogger.h"

/// Invoked during module startup.
Ring1_CheckReturn() Ring1_Result
Ring1_Loggers_notifyStartup
  (
  );

// Invoked during module shutdown.
void
Ring1_Loggers_notifyShutdown
  (
  );

/// @return A pointer to the standard error logger on success, a null pointer on failure.
/// @remark The logger is destroyed on shutdown.
Ring1_CheckReturn() Ring1_ConsoleLogger*
Ring1_Loggers_getOrCreateStandardErrorLogger
  (
  );

/// @return A pointer to the standard output logger on success, a null pointer on failure.
/// @remark The logger is destroyed on shutdown.
Ring1_CheckReturn() Ring1_ConsoleLogger*
Ring1_Loggers_getOrCreateStandardOutputLogger
  (
  );

#endif // RING1_LOG_LOGGERS_H_INCLUDED
