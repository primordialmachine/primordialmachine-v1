// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/ConsoleLogger.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_CONSOLELOGGER_H_INCLUDED)
#define RING1_LOG_CONSOLELOGGER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/ConsoleLogger.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Log/Logger.h"

Mkx_Type_DeclareEnumerationType("Ring1.ConsoleLogger.Color",
                                Ring1_ConsoleLogger_Color)

enum Ring1_ConsoleLogger_Color {
  Ring1_ConsoleLogger_Color_Default = (0),
  Ring1_ConsoleLogger_Color_Information = (1),
  Ring1_ConsoleLogger_Color_Warning = (2),
  Ring1_ConsoleLogger_Color_Error = (3),
};

Mkx_Type_DeclareClassType("Ring1.ConsoleLogger",
                          Mkx_ConsoleLogger,
                          MKX_CONSOLELOGGER)

struct Mkx_ConsoleLogger {
  Mkx_Logger parent;
  Ring1_ConsoleLogger_Color color;
};

struct Mkx_ConsoleLogger_Dispatch {
  Mkx_Logger_Dispatch parent;
  Ring1_Result (*getColor)(Ring1_ConsoleLogger_Color *result, Mkx_ConsoleLogger* self);
  Ring1_Result (*setColor)(Mkx_ConsoleLogger* self, Ring1_ConsoleLogger_Color color);
};

Ring1_CheckReturn() Ring1_Result
Mkx_ConsoleLogger_construct
  (
    Mkx_ConsoleLogger* self
  );

Ring1_CheckReturn() Ring1_Result
Mkx_ConsoleLogger_setColor
  (
    Mkx_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  );
  
Ring1_CheckReturn() Ring1_Result
Mkx_ConsoleLogger_getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Mkx_ConsoleLogger* self
  );

#endif  // RING1_LOG_CONSOLELOGGER_H_INCLUDED
