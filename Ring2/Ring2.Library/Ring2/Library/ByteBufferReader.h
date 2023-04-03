// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ByteBufferReader.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_BYTEBUFFERREADER_H_INCLUDED)
#define RING2_LIBRARY_BYTEBUFFERREADER_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ByteBufferReader.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/Library/ByteBuffer.h"

MACHINE_DECLARE_CLASSTYPE(Ring2_ByteBufferReader)

void
Ring2_ByteBufferReader_construct
  (
    Ring2_ByteBufferReader* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a Byte buffer reader.
/// @param byteBuffer The byte buffer.
/// @return The Byte buffer reader.
Ring1_NoDiscardReturn() Ring2_ByteBufferReader*
Ring2_ByteBufferReader_create
  (
    Ring2_ByteBuffer* byteBuffer
  );

/// @brief Get the position.
/// @param self This Byte buffer reader.
/// @return The position.
Ring1_NoDiscardReturn() int64_t
Ring2_ByteBufferReader_getPosition
  (
    Ring2_ByteBufferReader* self
  );

/// @brief Read up to @a n Bytes.
/// @param self This Byte buffer reader.
/// @param p A pointer to a buffer of at least @a n Bytes.
/// @param n The number of Bytes to read.
/// @param m A pointer to a variable. Receives the number of Bytes read.
void
Ring2_ByteBufferReader_read
  (
    Ring2_ByteBufferReader* self,
    char* p,
    int64_t n,
    int64_t* m
  );

#endif // RING2_LIBRARY_BYTEBUFFERREADER_H_INCLUDED
