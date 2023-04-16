// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Loggers.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/Loggers.h"
#undef RING1_PRIVATE

#define RING1_PRIVATE (1)
#include "Ring1/Log/DefaultConsoleLogger.h"
#undef RING1_PRIVATE

#include "Ring1/Console.h"

// The standard output logger.
static Ring1_ConsoleLogger* g_standardOutputLogger = NULL;

// The standard error logger.
static Ring1_ConsoleLogger* g_standardErrorLogger = NULL;

static Ring1_Console_ModuleHandle g_consoleModuleHandle = Ring1_Console_ModuleHandle_Invalid;

Ring1_CheckReturn() Ring1_Result
Ring1_Loggers_notifyStartup
  (
  )
{
  g_consoleModuleHandle = Ring1_Console_ModuleHandle_acquire();
  if (Ring1_Unlikely(!g_consoleModuleHandle)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void
Ring1_Loggers_notifyShutdown
  (
  )
{
  if (g_standardOutputLogger) {
    Ring1_Logger_unref(RING1_LOGGER(g_standardOutputLogger));
    g_standardOutputLogger = NULL;
  }
  if (g_standardErrorLogger) {
    Ring1_Logger_unref(RING1_LOGGER(g_standardErrorLogger));
    g_standardErrorLogger = NULL;
  }
  if (g_consoleModuleHandle) {
    Ring1_Console_ModuleHandle_relinquish(g_consoleModuleHandle);
    g_consoleModuleHandle = Ring1_Console_ModuleHandle_Invalid;
  }
}

Ring1_CheckReturn() Ring1_ConsoleLogger*
Ring1_Loggers_getOrCreateStandardErrorLogger
  (
  )
{
  if (Ring1_Unlikely(!g_standardErrorLogger)) {
    g_standardErrorLogger = RING1_CONSOLELOGGER(Ring1_DefaultConsoleLogger_createStandardError());
    if (Ring1_Unlikely(!g_standardErrorLogger)) {
      return NULL;
    }
  }
  return g_standardErrorLogger;
}

Ring1_CheckReturn() Ring1_ConsoleLogger*
Ring1_Loggers_getOrCreateStandardOutputLogger
  (
  )
{
  if (Ring1_Unlikely(!g_standardOutputLogger)) {
    g_standardOutputLogger = RING1_CONSOLELOGGER(Ring1_DefaultConsoleLogger_createStandardOutput());
    if (Ring1_Unlikely(!g_standardOutputLogger)) {
      return NULL;
    }
  }
  return g_standardOutputLogger;
}
