// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/LogBuffer.c
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/LogBuffer.h"
#undef RING1_PRIVATE

#include "Ring1/Status.h"
#include <malloc.h>
#include <stdio.h>


Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_create
  (
    Ring1_LogBuffer** buffer
  )
{
  if (!buffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_LogBuffer* buffer1 = malloc(sizeof(Ring1_LogBuffer));
  if (!buffer1) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  buffer1->size = 0;
  buffer1->capacity = 0;
  buffer1->elements = malloc(1);
  if (!buffer1->elements) {
    free(buffer1);
    buffer1 = NULL;
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  *buffer = buffer1;
  return Ring1_Result_Success;
}

void
Ring1_LogBuffer_destroy
  (
    Ring1_LogBuffer* buffer
  )
{
  if (buffer) {
    free(buffer->elements);
    free(buffer);
  }
}

Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_endsWithNewLine
  (
    bool *result,
    Ring1_LogBuffer* buffer
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!buffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (0 == buffer->size) {
    // The buffer is empty.
    *result = false;
  } else {
    // The buffer is not empty.
    size_t index = buffer->size - 1;
    // Covers '\n', '\r', as well as '\n\r' and '\r\n'.
    *result = buffer->elements[index] == '\n' || buffer->elements[index] == '\r';
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_ensureFreeCapacity
  (
    Ring1_LogBuffer* buffer,
    size_t n
  )
{
  size_t m = buffer->capacity - buffer->size;
  if (m < n) {
    size_t d = n - m;
    if (SIZE_MAX - d < buffer->capacity) { // SIZE_MAX < c + d ~ SIZE_MAX - d < c
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    size_t new_capacity = buffer->capacity + d;
    char* new_elements = realloc(buffer->elements, new_capacity);
    if (!new_elements) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    buffer->elements = new_elements;
    buffer->capacity = new_capacity;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_append_fv
  (
    Ring1_LogBuffer* buffer,
    char const* format,
    va_list arguments
  )
{
  if (!buffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!format) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  int result[2];
  // Count the number of characters (including the terminator 0 character).
  char temporary[1];
  va_list args[2];
  va_copy(args[0], arguments);
  va_copy(args[1], arguments);
  result[0] = vsnprintf(temporary, 0, format, args[0]);
  if (-1 == result[0]) {
    Ring1_Status_set(Ring1_Status_EncodingError);
    return Ring1_Result_Failure;
  }
  if (0 == result[0]) {
    // Zero length message.
    return Ring1_Result_Success;
  }
  // Ensure there is enough free capacity.
  if (Ring1_LogBuffer_ensureFreeCapacity(buffer, (size_t)result[0] + 1)) {
    return Ring1_Result_Failure;
  }
  // Print the character (including the terminator 0 character).
  result[1] = vsnprintf(buffer->elements + buffer->size,
                        buffer->capacity - buffer->size, format, args[1]);
  if (result[0] != result[1]) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  // Update the buffer size.
  buffer->size += result[1];

  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_append_f
  (
    Ring1_LogBuffer* buffer,
    char const* format,
    ...
  )
{
  va_list arguments;
  va_start(arguments, format);
  Ring1_Result result = Ring1_LogBuffer_append_fv(buffer, format, arguments);
  va_end(arguments);
  return result;
}

Ring1_CheckReturn() Ring1_Result
Ring1_LogBuffer_removeCarriageReturns
  (
    Ring1_LogBuffer* buffer
  )
{
  if (!buffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (buffer->size == 0) {
    return Ring1_Result_Success;
  }
  char* p = malloc(buffer->size);
  if (!p) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  size_t k = 0;
  for (size_t i = 0, n = buffer->size; i < n; ++i) {
    if (buffer->elements[i] != '\r') {
      p[k++] = buffer->elements[i];
    }
  }
  free(buffer->elements);
  buffer->elements = p;
  buffer->size = k;
  buffer->capacity = k;
  return Ring1_Result_Success;
}
