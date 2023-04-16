// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/ConsoleLogger.h
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_CONSOLELOGGER_H_INCLUDED)
#define RING1_LOG_CONSOLELOGGER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/ConsoleLogger.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Log/Logger.h"
#include "Ring1/Log/ConsoleLogger_Color.h"


typedef struct Ring1_ConsoleLogger Ring1_ConsoleLogger;

static inline Ring1_ConsoleLogger *RING1_CONSOLELOGGER(void *pointer) {
  return (Ring1_ConsoleLogger *)pointer;
}

struct Ring1_ConsoleLogger {
  Ring1_Logger parent;
  Ring1_ConsoleLogger_Color color;
  Ring1_Result (*getColor)(Ring1_ConsoleLogger_Color *result, Ring1_ConsoleLogger* self);
  Ring1_Result (*setColor)(Ring1_ConsoleLogger* self, Ring1_ConsoleLogger_Color color);
};

Ring1_CheckReturn() Ring1_Result
Ring1_ConsoleLogger_construct
  (
    Ring1_ConsoleLogger* self
  );
  
void
Ring1_ConsoleLogger_destruct
  (
    Ring1_ConsoleLogger* self
  );

Ring1_CheckReturn() Ring1_Result
Ring1_ConsoleLogger_setColor
  (
    Ring1_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  );
  
Ring1_CheckReturn() Ring1_Result
Ring1_ConsoleLogger_getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Ring1_ConsoleLogger* self
  );

#endif  // RING1_LOG_CONSOLELOGGER_H_INCLUDED
