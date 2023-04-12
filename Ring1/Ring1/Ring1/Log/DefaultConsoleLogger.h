// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Log/DefaultConsoleLogger.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_DEFAULTCONSOLELOGGER_H_INCLUDED)
#define RING1_LOG_DEFAULTCONSOLELOGGER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/DefaultConsoleLogger.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Log/ConsoleLogger.h"
#include "Ring1/Console.h"

Mkx_Type_DeclareClassType("Ring1.DefaultConsoleLogger",
                          Mkx_DefaultConsoleLogger,
                          MKX_DEFAULTCONSOLELOGGER)

struct Mkx_DefaultConsoleLogger {
  Mkx_ConsoleLogger parent;
  Ring1_Console_Connection* connection;
};

struct Mkx_DefaultConsoleLogger_Dispatch
{
  Mkx_ConsoleLogger_Dispatch parent;
};

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_DefaultConsoleLogger_construct
  (
    Mkx_DefaultConsoleLogger *self,
    Ring1_Console_Connection *connection
  );

Ring1_CheckReturn() int
Mkx_DefaultConsoleLogger_create
  (
    Mkx_DefaultConsoleLogger** result,
    Ring1_Console_Connection *connection
  );

Ring1_CheckReturn() Mkx_DefaultConsoleLogger*
Mkx_DefaultConsoleLogger_createStandardError
  (
  );

Ring1_CheckReturn() Mkx_DefaultConsoleLogger*
Mkx_DefaultConsoleLogger_createStandardOutput
  (
  );

void
Mkx_DefaultConsoleLogger_destruct
  (
    Mkx_DefaultConsoleLogger* logger
  );

#endif  // RING1_LOG_DEFAULTCONSOLELOGGER_H_INCLUDED
