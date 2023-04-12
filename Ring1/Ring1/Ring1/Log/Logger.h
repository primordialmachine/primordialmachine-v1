// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Logger.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_LOGGER_H_INCLUDED)
#define RING1_LOG_LOGGER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/ConsoleLogger.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Mkx/Object.h"

Mkx_Type_DeclareClassType("Ring1.Logger",
                          Mkx_Logger,
                          MKX_LOGGER);

struct Mkx_Logger {
  Mkx_Object parent;
};

struct Mkx_Logger_Dispatch {
  Mkx_Object_Dispatch parent;
  Ring1_Result (*write)(Mkx_Logger* self, const char* bytes, size_t numberOfBytes);
};

Ring1_CheckReturn() Ring1_Result
Mkx_Logger_construct
  (
    Mkx_Logger *self
  );

Ring1_CheckReturn() Ring1_Result
Mkx_Logger_write
  (
    Mkx_Logger* self,
    const char* bytes,
    size_t numberOfBytes
  );

#endif // RING1_LOG_LOGGER_H_INCLUDED
