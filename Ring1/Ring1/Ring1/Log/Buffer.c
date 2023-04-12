// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Buffer.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/Buffer.h"
#undef RING1_PRIVATE

#include <malloc.h>
#include <stdio.h>

Ring1_CheckReturn() Mkx_Log_Buffer*
Mkx_Log_Buffer_create
  (
  )
{
  Mkx_Log_Buffer* buffer = malloc(sizeof(Mkx_Log_Buffer));
  if (!buffer)
    return NULL;
  buffer->size = 0;
  buffer->capacity = 0;
  buffer->elements = malloc(1);
  if (!buffer->elements) {
    free(buffer);
    return NULL;
  }
  return buffer;
}

void
Mkx_Log_Buffer_destroy
  (
    Mkx_Log_Buffer* buffer
  )
{
  if (buffer)
  {
    free(buffer->elements);
    free(buffer);
  }
}

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_endsWithNewLine
  (
    bool *result,
    Mkx_Log_Buffer* buffer
  )
{
  if (buffer->size == 0) {
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
Mkx_Log_Buffer_ensureFreeCapacity
  (
    Mkx_Log_Buffer* buffer,
    size_t n
  )
{
  size_t m = buffer->capacity - buffer->size;
  if (m < n)
  {
    size_t d = n - m;
    if (SIZE_MAX - d < buffer->capacity)  // SIZE_MAX < c + d ~ SIZE_MAX - d < c
      return 1;
    size_t new_capacity = buffer->capacity + d;
    char* new_elements = realloc(buffer->elements, new_capacity);
    if (!new_elements) {
      return 1;
    }
    buffer->elements = new_elements;
    buffer->capacity = new_capacity;
  }
  return 0;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_append_fv
  (
    Mkx_Log_Buffer* buffer,
    const char* format,
    va_list arguments
  )
{
  if (!buffer || !format)
    return 1;
  int result[2];
  // Count the number of characters (including the terminator 0 character).
  char temporary[1];
  va_list args[2];
  va_copy(args[0], arguments);
  va_copy(args[1], arguments);
  result[0] = vsnprintf(temporary, 0, format, args[0]);
  if (-1 == result[0]) {
    // Encoding error.
    return 1;
  }
  if (0 == result[0]) {
    // Zero length message.
    return 0;
  }
  // Ensure there is enough free capacity.
  if (Mkx_Log_Buffer_ensureFreeCapacity(buffer, (size_t)result[0] + 1)) {
    return 1;
  }
  // Print the character (including the terminator 0 character).
  result[1] = vsnprintf(buffer->elements + buffer->size,
                        buffer->capacity - buffer->size, format, args[1]);
  if (result[0] != result[1]) {
    // Environment error.
    return 1;
  }
  // Update the buffer size.
  buffer->size += result[1];

  return 0;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_append_f
  (
    Mkx_Log_Buffer* buffer,
    const char* format,
    ...
  )
{
  va_list arguments;
  va_start(arguments, format);
  int result = Mkx_Log_Buffer_append_fv(buffer, format, arguments);
  va_end(arguments);
  return result;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Log_Buffer_removeCarriageReturns
  (
    Mkx_Log_Buffer* buffer
  )
{
  if (!buffer)
    return 1;
  if (buffer->size == 0)
    return 0;
  char* p = malloc(buffer->size);
  if (!p) {
    return 1;
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
  return 0;
}
