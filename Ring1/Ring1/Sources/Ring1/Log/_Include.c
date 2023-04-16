// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#define RING1_PRIVATE (1)
#include "Ring1/Log/_Include.h"
#undef RING1_PRIVATE

#define RING1_PRIVATE (1)
#include "Ring1/Log/Loggers.h"
#include "Ring1/Log/LogBuffer.h"
#include "Ring1/Log/Event.h"
#undef RING1_PRIVATE


// The buffer.
static Ring1_LogBuffer* g_logBuffer = NULL;


static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, Log, initializeModule, uninitializeModule)

static void
uninitializeModule
  (
    void
  )
{
  if (g_logBuffer) {
    Ring1_LogBuffer_destroy(g_logBuffer);
    g_logBuffer = NULL;
  }
  Ring1_Loggers_notifyShutdown();
}

static Ring1_Result
initializeModule
  (
  )
{
  if (Ring1_Unlikely(Ring1_Loggers_notifyStartup())) {
    return Ring1_Result_Failure;
  }
  // Ensure the buffer object exists.
  if (!g_logBuffer) {
    if (Ring1_LogBuffer_create(&g_logBuffer)) {
      Ring1_Loggers_notifyShutdown();
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

void
Ring1_Log_logEvent
  (
    Event* event
  )
{
  char const* level_string = NULL;
  Ring1_ConsoleLogger* logger = NULL;
  switch (event->level) {
  case Ring1_Log_Level_Information:
  case Ring1_Log_Level_Warning: {
    logger = Ring1_Loggers_getOrCreateStandardOutputLogger();
  } break;
  case Ring1_Log_Level_Error: {
    logger = Ring1_Loggers_getOrCreateStandardErrorLogger();
  } break;
  default: {
    return;
  }
  };
  if (!logger) return;
  switch (event->level) {
  case Ring1_Log_Level_Information: {
    level_string = "information: ";
  } break;
  case Ring1_Log_Level_Warning: {
    level_string = "warning:     ";
  } break;
  case Ring1_Log_Level_Error: {
    level_string = "error:       ";
  } break;
  default: {
    return;
  }
  };
  g_logBuffer->size = 0;
  if (Ring1_LogBuffer_append_f(g_logBuffer, "%s\n", level_string)) {
    return;
  }
  if (Ring1_LogBuffer_append_f(g_logBuffer, "file: %s, line: %d\n", event->file, event->line)) {
    return;
  }
  if (Ring1_LogBuffer_append_fv(g_logBuffer, event->format, event->arguments)) {
    return;
  }
  bool result;
  if (Ring1_LogBuffer_endsWithNewLine(&result, g_logBuffer)) {
    return;
  }
  if (!result) {
    if (Ring1_LogBuffer_append_f(g_logBuffer, "\n")) {
      return;
    }
  }
  // Remove carriage returns.
  if (Ring1_LogBuffer_removeCarriageReturns(g_logBuffer)) {
    return;
  }
  switch (event->level) {
  case Ring1_Log_Level_Information: {
    Ring1_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Information);
  } break;
  case Ring1_Log_Level_Warning: {
    Ring1_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Warning);
  } break;
  case Ring1_Log_Level_Error: {
    Ring1_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Error);
  } break;
  default: {
    return;
  }
  };
  Ring1_Logger_write(RING1_LOGGER(logger), g_logBuffer->elements, g_logBuffer->size);
  Ring1_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Default);
}

void
Ring1_log_fv
  (
    int level,
    char const* file,
    int line,
    char const* format,
    va_list arguments
  )
{
  Ring1_Log_Module_lock();
  if (!Ring1_Log_Module_isInitialized()) {
    Ring1_Log_Module_unlock();
    return;
  }
  Event event;
  Event_setData(&event, level, file, line, format, arguments);
  Ring1_Log_logEvent(&event);
  Ring1_Log_Module_unlock();
}

void
Ring1_log_f
  (
    int level,
    char const* file,
    int line,
    char const* format,
    ...
  )
{
  va_list arguments;
  va_start(arguments, format);
  Ring1_log_fv(level, file, line, format, arguments);
  va_end(arguments);
}
