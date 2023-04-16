// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Buffer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_LOG_LOGBUFFER_H_INCLUDED)
#define RING1_LOG_LOGBUFFER_H_INCLUDED

#if !defined(RING1_PRIVATE) || 1 != RING1_PRIVATE
#error("Do not include 'Ring1/Log/LogBuffer.h' directly. Include 'Ring1/Log.h' instead.")
#endif
#include "Ring1/Result.h"
#include "Ring1/Intrinsic/_Include.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct Ring1_LogBuffer {
  char* elements;
  size_t size, capacity;
} Ring1_LogBuffer;

/// @brief Create a log buffer.
/// @param buffer A pointer to a <code>Ring1_Log_Buffer*</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success <code>*buffer</code> was assigned a pointer to the @a Ring1_Log_Buffer.
/// @failure This function set the by-thread error variable.
Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_create
  (
    Ring1_LogBuffer** buffer
  );

/// @brief Destroy a log buffer.
/// @param buffer A pointer to an Ring1_Log_Buffer object or a null pointer.
/// @remark This function silently ignores null pointers passed through @a buffer.
void
Ring1_LogBuffer_destroy
  (
    Ring1_LogBuffer *buffer
  );

/// @success <code>*result</code> was assigned @a true if the string ends with a newline ('\n', '\r', '\r\n', '\n\r') sequence. @a false otherwise.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @failure This function set the by thread error variable.
Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_endsWithNewLine
  (
    bool *result,
    Ring1_LogBuffer* buffer
  );

/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @failure This function set the by thread error variable.
Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_ensureFreeCapacity
  (
    Ring1_LogBuffer* buffer,
    size_t n
  );

/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @failure This function set the by thread error variable.
Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_append_fv
  (
    Ring1_LogBuffer* buffer,
    const char* format,
    va_list arguments
  );

/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @failure This function set the by thread error variable.
Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_append_f
  (
    Ring1_LogBuffer* buffer,
    char const* format,
    ...
  );

/// @brief Remove all carriage returns in the buffer.
/// @param buffer A pointer to the log buffer.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @failure This function set the by thread error variable.
Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_removeCarriageReturns
  (
    Ring1_LogBuffer *buffer
  );

#endif // RING1_LOG_LOGBUFFER_H_INCLUDED
