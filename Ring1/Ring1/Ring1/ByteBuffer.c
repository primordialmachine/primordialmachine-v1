// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/ByteBuffer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/ByteBuffer.h"


#include "Ring1/Status.h"
#include "Ring1/Memory.h"


#define Ring1_ByteBuffer_TraceEnabled (1)

#if defined(Ring1_ByteBuffer_TraceEnabled) && 1 == Ring1_ByteBuffer_TraceEnabled

  #include <stdio.h>
  #include <stdarg.h>

  static void
  TRACE
    (
      const char* format,
      ...
    )
  {
    va_list arguments;
    va_start(arguments, format);
    vfprintf(stdout, format, arguments);
    va_end(arguments);
  }

#else

  static void
  TRACE
    (
      const char* format,
      ...
    )
  {}

#endif

typedef struct Handles
{
  Ring1_Memory_ModuleHandle memory;
} Handles;

static Handles g_handles = { .memory = Ring1_Memory_ModuleHandle_Invalid };

static Ring1_Result
initializeModule
  (
  )
{
  g_handles.memory = Ring1_Memory_ModuleHandle_acquire();
  if (!g_handles.memory) return Ring1_Result_Failure;
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  Ring1_Memory_ModuleHandle_relinquish(g_handles.memory);
  g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
}

Ring1_Module_Define(Ring1, ByteBuffer, initializeModule, uninitializeModule)

typedef struct Impl
{
  char* elements;
  size_t size, capacity;
} Impl;

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
increaseCapacity
  (
    Impl *pimpl,
    size_t additionalCapacity
  )
{
  if (!pimpl) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (additionalCapacity == 0) {
    return Ring1_Result_Success;
  }
  size_t oldCapacity = pimpl->capacity,
         newCapacity;
  if (Ring1_Memory_recomputeSize_sz(Ring1_ByteBuffer_Capacity_Least, Ring1_ByteBuffer_Capacity_Greatest,
                                    oldCapacity, additionalCapacity, &newCapacity, true)) {
    return Ring1_Result_Failure;
  }
  void *oldElements = pimpl->elements,
       *newElements = NULL;
  if (Ring1_Memory_allocate(&newElements, newCapacity)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Memory_copyArrayFast(newElements, oldElements, pimpl->size, sizeof(char))) {
    Ring1_Status_set(Ring1_Status_Success);
    Ring1_Memory_deallocate(newElements);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_deallocate(oldElements);
  pimpl->elements = newElements;
  pimpl->capacity = newCapacity;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
initialize
  (
    Impl *pimpl
  )
{
  pimpl->size = 0;
  pimpl->capacity = Ring1_ByteBuffer_Capacity_Default;
  pimpl->elements = NULL;
  return Ring1_Memory_allocateArray(&pimpl->elements, Ring1_ByteBuffer_Capacity_Default, sizeof(char));
}

static inline void
uninitialize
  (
    Impl *pimpl
  )
{
  if (pimpl->elements)
  {
    Ring1_Memory_deallocate(pimpl->elements);
    pimpl->elements = NULL;
  }
  pimpl->capacity = 0;
  pimpl->size = 0;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
insertBytesAt
  (
    Impl* pimpl,
    size_t index,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (!pimpl || !bytes) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (index > pimpl->size) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  size_t freeCapacity = pimpl->capacity - pimpl->size;
  if (freeCapacity < numberOfBytes) {
    size_t additionalCapacity = numberOfBytes - freeCapacity;
    if (increaseCapacity(pimpl, additionalCapacity)) {
      return Ring1_Result_Failure;
    }
  }
  if (index < pimpl->size) {
    Ring1_Memory_copySlow(pimpl->elements + index + numberOfBytes,
                          pimpl->elements + index,
                          pimpl->size - index);
  }
  Ring1_Memory_copyFast(pimpl->elements + index,
                        bytes,
                        numberOfBytes);
  pimpl->size += numberOfBytes;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
insertByteAt
  (
    Impl* pimpl,
    size_t index,
    char byte
  )
{ return insertBytesAt(pimpl, index, &byte, 1); }

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
appendByte
  (
    Impl *pimpl,
    char byte
  )
{ return insertByteAt(pimpl, pimpl->size, byte); }

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
appendBytes
  (
    Impl *pimpl,
    const char *bytes,
    size_t numberOfBytes
  )
{ return insertBytesAt(pimpl, pimpl->size, bytes, numberOfBytes); }

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
prependByte
  (
    Impl* pimpl,
    char byte
  )
{ return insertByteAt(pimpl, 0, byte); }

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
prependBytes
  (
    Impl* pimpl,
    char const* bytes,
    size_t numberOfBytes
  )
{ return insertBytesAt(pimpl, 0, bytes, numberOfBytes); }

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
clear
  (
    Impl *pimpl
  )
{ 
  if (!pimpl) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  pimpl->size = 0;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
getBytes
  (
    char const **result,
    Impl *pimpl
  )
{
  if (!result || !pimpl) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = pimpl->elements;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
getNumberOfBytes
  (
    size_t *result,
    Impl *pimpl
  )
{ 
  if (!result || !pimpl) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = pimpl->size;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_initialize
  (
    Ring1_ByteBuffer* byteBuffer
  )
{
  Impl* pimpl;
  if (Ring1_Memory_allocate(&pimpl, sizeof(Impl))) {
    return Ring1_Result_Failure;
  }
  if (initialize(pimpl)) {
    Ring1_Memory_deallocate(pimpl);
    return Ring1_Result_Failure;
  }
  byteBuffer->pimpl = pimpl;
  return Ring1_Result_Success;
}

void 
Ring1_ByteBuffer_uninitialize
  (
    Ring1_ByteBuffer* byteBuffer
  )
{
  Impl *pimpl = byteBuffer->pimpl;
  uninitialize(pimpl);
  Ring1_Memory_deallocate(pimpl);
  byteBuffer->pimpl = NULL;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_insertByteAt
  (
    Ring1_ByteBuffer* byteBuffer,
    size_t index,
    char byte
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return insertByteAt(byteBuffer->pimpl, index, byte);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_insertBytesAt
  (
    Ring1_ByteBuffer* byteBuffer,
    size_t index,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return insertBytesAt(byteBuffer->pimpl, index, bytes, numberOfBytes);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_appendByte
  (
    Ring1_ByteBuffer* byteBuffer,
    char byte
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return appendByte(byteBuffer->pimpl, byte);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_appendBytes
  (
    Ring1_ByteBuffer* byteBuffer,
    const char* bytes,
    size_t numberOfBytes
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return appendBytes(byteBuffer->pimpl, bytes, numberOfBytes);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_prependByte
  (
    Ring1_ByteBuffer* byteBuffer,
    char byte
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return prependByte(byteBuffer->pimpl, byte);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_prependBytes
  (
    Ring1_ByteBuffer* byteBuffer,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return prependBytes(byteBuffer->pimpl, bytes, numberOfBytes);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_clear
  (
    Ring1_ByteBuffer* byteBuffer
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return clear(byteBuffer->pimpl);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_getBytes
  (
    char const **result,
    Ring1_ByteBuffer const* byteBuffer
  )
{
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return getBytes(result, byteBuffer->pimpl);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ByteBuffer_getNumberOfBytes
  (
    size_t *result,
    Ring1_ByteBuffer const* byteBuffer
  )
{ 
  if (!byteBuffer) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return getNumberOfBytes(result, byteBuffer->pimpl);
}
