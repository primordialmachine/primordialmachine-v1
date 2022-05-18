// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/ByteBuffer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_BYTEBUFFER_H_INCLUDED)
#define RING1_BYTEBUFFER_H_INCLUDED

#include "Ring1/Module.h"
#include "Ring1/Result.h"
#include "Ring1/Intrinsic/CheckReturn.h"

Ring1_Module_Declare(ByteBuffer)

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer
typedef struct Ring1_ByteBuffer { void *pimpl; } Ring1_ByteBuffer;

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_initialize
Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_initialize
  (
    Ring1_ByteBuffer *byteBuffer
  );

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_uninitialize
void
Ring1_ByteBuffer_uninitialize
  (
    Ring1_ByteBuffer *byteBuffer
  );

Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_insertByteAt
  (
    Ring1_ByteBuffer* byteBuffer,
    size_t index,
    char byte
  );

Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_insertBytesAt
  (
    Ring1_ByteBuffer* byteBuffer,
    size_t index,
    char const* bytes,
    size_t numberOfBytes
  );

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_appendByte
Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_appendByte
  (
    Ring1_ByteBuffer* byteBuffer,
    char byte
  );

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_appendBytes
Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_appendBytes
  (
    Ring1_ByteBuffer* byteBuffer,
    char const* bytes,
    size_t numberOfBytes
  );

Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_prependByte
  (
    Ring1_ByteBuffer* byteBuffer,
    char byte
  );

Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_prependBytes
  (
    Ring1_ByteBuffer* byteBuffer,
    char const* bytes,
    size_t numberOfBytes
  );

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_clear
Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_clear
  (
    Ring1_ByteBuffer* byteBuffer
  );

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_getBytes
Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_getBytes
  (
    char const **result,
    Ring1_ByteBuffer const* byteBuffer
  );

// https://documentation.primordialmachine.com/api/ring1-library/bytebuffer-library/Ring1_ByteBuffer_getNumberOfBytes
Ring1_CheckReturn() Ring1_Result
Ring1_ByteBuffer_getNumberOfBytes
  (
    size_t *result,
    Ring1_ByteBuffer const* byteBuffer
  );

#endif // RING1_BYTEBUFFER_H_INCLUDED
