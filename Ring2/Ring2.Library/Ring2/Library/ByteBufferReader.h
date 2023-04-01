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


MACHINE_DECLARE_CLASSTYPE(Machine_ByteBufferReader)

void Machine_ByteBufferReader_construct(Machine_ByteBufferReader* self, size_t numberOfArguments,
                                        Ring2_Value const* arguments);

/// @brief Create a Byte buffer reader.
/// @param byteBuffer The byte buffer.
/// @return The Byte buffer reader.
Ring1_NoDiscardReturn() Machine_ByteBufferReader*
Machine_ByteBufferReader_create
  (
    Ring2_ByteBuffer* byteBuffer
  );

/// @brief Get the position.
/// @param self This Byte buffer reader.
/// @return The position.
size_t
Machine_ByteBufferReader_getPosition
  (
    Machine_ByteBufferReader* self
  );

/// @brief Read up to @a n Bytes.
/// @param self This Byte buffer reader.
/// @param p A pointer to a buffer of at least @a n Bytes.
/// @param n The number of Bytes to read.
/// @param m A pointer to a variable. Receives the number of Bytes read.
void
Machine_ByteBufferReader_read
  (
    Machine_ByteBufferReader* self,
    char* p,
    size_t n,
    size_t* m
  );


#endif // RING2_LIBRARY_BYTEBUFFERREADER_H_INCLUDED
