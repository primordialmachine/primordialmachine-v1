// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Logger.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_LOGGER_H_INCLUDED)
#define RING1_LOG_LOGGER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/Logger.h' directly, include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Intrinsic/_Include.h"
#if 0
//#include "Mkx/Object.h"
#endif

typedef struct Ring1_Logger Ring1_Logger;

static inline Ring1_Logger *RING1_LOGGER(void *pointer) {
  return (Ring1_Logger *)pointer;
}

struct Ring1_Logger {
  int64_t referenceCount;
  Ring1_Result (*write)(Ring1_Logger* self, char const* bytes, size_t numberOfBytes);
  void (*destruct)(Ring1_Logger* self);
};

void
Ring1_Logger_ref
  (
    Ring1_Logger *self
  );
  
void
Ring1_Logger_unref
  (
    Ring1_Logger *self
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Logger_construct
  (
    Ring1_Logger *self
  );

void
Ring1_Logger_destruct
  (
    Ring1_Logger* self
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Logger_write
  (
    Ring1_Logger* self,
    char const* bytes,
    size_t numberOfBytes
  );


#endif // RING1_LOG_LOGGER_H_INCLUDED
