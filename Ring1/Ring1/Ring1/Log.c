// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#define RING1_PRIVATE (1)
#include "Ring1/Log.h"
#undef RING1_PRIVATE


#define RING1_PRIVATE (1)
#include "Ring1/Log/Loggers.h"
#include "Ring1/Log/Buffer.h"
#include "Ring1/Log/Event.h"
#undef RING1_PRIVATE


#include "Mkx/Object.h"


// The buffer.
static Mkx_Log_Buffer* g_buffer = NULL;


static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, Log, initializeModule, uninitializeModule)

typedef struct Handles {
  Ring1_ObjectModule_ModuleHandle object;
} Handles;

static Handles g_handles = { .object = Ring1_ObjectModule_ModuleHandle_Invalid };

static void
uninitializeModule
  (
    void
  )
{
  if (g_buffer) {
    Mkx_Log_Buffer_destroy(g_buffer);
    g_buffer = NULL;
  }
  Mkx_Log_Loggers_notifyShutdown();
  Ring1_ObjectModule_ModuleHandle_relinquish(g_handles.object);
  g_handles.object = Ring1_ObjectModule_ModuleHandle_Invalid;
}

static Ring1_Result
initializeModule
  (
  )
{
  g_handles.object = Ring1_ObjectModule_ModuleHandle_acquire();
  if (!g_handles.object) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Mkx_Log_Loggers_notifyStartup())) { 
    Ring1_ObjectModule_ModuleHandle_relinquish(g_handles.object);
    g_handles.object = Ring1_ObjectModule_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  // Ensure the buffer object exists.
  if (!g_buffer) {
    g_buffer = Mkx_Log_Buffer_create();
    if (!g_buffer) {
      Mkx_Log_Loggers_notifyShutdown();
      Ring1_ObjectModule_ModuleHandle_relinquish(g_handles.object);
      g_handles.object = Ring1_ObjectModule_ModuleHandle_Invalid;
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}


void
Mkx_Log_logEvent
  (
    Event* event
  )
{
  char const* level_string = NULL;
  Mkx_ConsoleLogger* logger = NULL;
  switch (event->level) {
  case Ring1_Log_Level_Information:
  case Ring1_Log_Level_Warning: {
    logger = Mkx_Log_Loggers_getOrCreateStandardOutputLogger();
  } break;
  case Ring1_Log_Level_Error: {
    logger = Mkx_Log_Loggers_getOrCreateStandardErrorLogger();
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
  g_buffer->size = 0;
  if (Mkx_Log_Buffer_append_f(g_buffer, "%s\n", level_string)) {
    return;
  }
  if (Mkx_Log_Buffer_append_f(g_buffer, "file: %s, line: %d\n", event->file, event->line)) {
    return;
  }
  if (Mkx_Log_Buffer_append_fv(g_buffer, event->format, event->arguments)) {
    return;
  }
  bool result;
  if (Mkx_Log_Buffer_endsWithNewLine(&result, g_buffer)) {
    return;
  }
  if (!result) {
    if (Mkx_Log_Buffer_append_f(g_buffer, "\n")) {
      return;
    }
  }
  // Remove carriage returns.
  if (Mkx_Log_Buffer_removeCarriageReturns(g_buffer)) {
    return;
  }
  switch (event->level) {
  case Ring1_Log_Level_Information: {
    Mkx_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Information);
  } break;
  case Ring1_Log_Level_Warning: {
    Mkx_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Warning);
  } break;
  case Ring1_Log_Level_Error: {
    Mkx_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Error);
  } break;
  default: {
    return;
  }
  };
  Mkx_Logger_write(MKX_LOGGER(logger), g_buffer->elements, g_buffer->size);
  Mkx_ConsoleLogger_setColor(logger, Ring1_ConsoleLogger_Color_Default);
}

void
Ring1_log_fv
  (
    int level,
    const char* file,
    int line,
    const char* format,
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
  Mkx_Log_logEvent(&event);
  Ring1_Log_Module_unlock();
}

void
Ring1_log_f
  (
    int level,
    const char* file,
    int line,
    const char* format,
    ...
  )
{
  va_list arguments;
  va_start(arguments, format);
  Ring1_log_fv(level, file, line, format, arguments);
  va_end(arguments);
}
