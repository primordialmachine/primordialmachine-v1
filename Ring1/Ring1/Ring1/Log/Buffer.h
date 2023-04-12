// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Buffer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_BUFFER_H_INCLUDED)
#define RING1_LOG_BUFFER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/Buffer.h' directly. Include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Intrinsic/_Include.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct Mkx_Log_Buffer {
  char* elements;
  size_t size, capacity;
} Mkx_Log_Buffer;

/// @return A pointer to a _mkx_log_buffer object on success, a null pointer on failure.
Ring1_CheckReturn() Mkx_Log_Buffer*
Mkx_Log_Buffer_create
  (
  );

/// @param buffer A pointer to an Mkx_Log_Buffer object or a null pointer.
/// @remark This function silently ignores null pointers passed through @a buffer.
void
Mkx_Log_Buffer_destroy
  (
    Mkx_Log_Buffer *buffer
  );

/// @return @a true if the string ends with a newline ('\n', '\r', '\r\n', '\n\r') sequence, @a false otherwise.
Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_endsWithNewLine
  (
    bool *result,
    Mkx_Log_Buffer* buffer
  );

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_ensureFreeCapacity
  (
    Mkx_Log_Buffer* buffer,
    size_t n
  );

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_append_fv
  (
    Mkx_Log_Buffer* buffer,
    const char* format,
    va_list arguments
  );

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_append_f
  (
    Mkx_Log_Buffer* buffer,
    const char* format,
    ...
  );

/// @brief Remove all carriage returns in the buffer.
/// @param buffer A pointer to the log buffer.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_removeCarriageReturns
  (
    Mkx_Log_Buffer *buffer
  );

#endif // RING1_LOG_BUFFER_H_INCLUDED
