// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/DefaultConsoleLogger.h
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_DEFAULTCONSOLELOGGER_H_INCLUDED)
#define RING1_LOG_DEFAULTCONSOLELOGGER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/DefaultConsoleLogger.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Log/ConsoleLogger.h"
#include "Ring1/Console.h"


typedef struct Ring1_DefaultConsoleLogger Ring1_DefaultConsoleLogger;

static inline Ring1_DefaultConsoleLogger* RING1_DEFAULTCONSOLELOGGER(void* pointer) {
  return (Ring1_DefaultConsoleLogger*)pointer;
}

struct Ring1_DefaultConsoleLogger {
  Ring1_ConsoleLogger parent;
  Ring1_Console_Connection* connection;
};

Ring1_CheckReturn() Ring1_Result 
Ring1_DefaultConsoleLogger_construct
  (
    Ring1_DefaultConsoleLogger *self,
    Ring1_Console_Connection *connection
  );
  
void
Ring1_DefaultConsoleLogger_destruct
  (
    Ring1_DefaultConsoleLogger *self
  );

Ring1_CheckReturn() Ring1_Result
Ring1_DefaultConsoleLogger_create
  (
    Ring1_DefaultConsoleLogger** result,
    Ring1_Console_Connection *connection
  );

Ring1_CheckReturn() Ring1_DefaultConsoleLogger*
Ring1_DefaultConsoleLogger_createStandardError
  (
  );

Ring1_CheckReturn() Ring1_DefaultConsoleLogger*
Ring1_DefaultConsoleLogger_createStandardOutput
  (
  );


#endif  // RING1_LOG_DEFAULTCONSOLELOGGER_H_INCLUDED
