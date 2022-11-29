// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ByteBuffer.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_BYTEBUFFER_H_INCLUDED)
#define RING2_LIBRARY_BYTEBUFFER_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ByteBuffer.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


MACHINE_DECLARE_CLASSTYPE(Ring2_ByteBuffer)

/// @brief Create a Byte buffer.
/// @return The Byte buffer.
Ring2_ByteBuffer*
Ring2_ByteBuffer_create
  (
  );

/// @brief Append specified Bytes to this Byte buffer.
/// @param self This Byte buffer.
/// @param p, n The specified Bytes.
void
Ring2_ByteBuffer_appendBytes
  (
    Ring2_ByteBuffer* self,
    const char* p,
    size_t n
  );

/// @brief Prepend specified Bytes to this Byte buffer.
/// @param self This Byte buffer.
/// @param p, n The specified Bytes.
void
Ring2_ByteBuffer_prependBytes
  (
    Ring2_ByteBuffer* self,
    const char* p,
    size_t n
  );

/// @brief Insert specified Bytes to this Byte buffer.
/// @param self This Byte buffer.
/// @param i The index at which to insert the Bytes.
/// @param p, n The specified Bytes.
void
Ring2_ByteBuffer_insertBytesAt
  (
    Ring2_ByteBuffer* self,
    size_t i,
    const char* p,
    size_t n
  );

/// @brief Clear this Byte buffer.
/// @param self This Byte buffer.
void
Ring2_ByteBuffer_clear
  (
    Ring2_ByteBuffer* self
  );

/// @brief Get a pointer to the Byte of this Byte buffer.
/// @param self This Byte buffer.
/// @return A pointer to the Byte of this Byte buffer.
char const*
Ring2_ByteBuffer_getBytes
  (
    Ring2_ByteBuffer const* self
  );

/// @brief Get the number of Bytes of this Byte buffer.
/// @param self This Byte buffer.
/// @return The number of Bytes of this Byte buffer.
int64_t
Ring2_ByteBuffer_getNumberOfBytes
  (
    Ring2_ByteBuffer const* self
  );

/// @brief Compare the Bytes of this Byte buffer to the specified Bytes.
/// @param self This Byte buffer.
/// @param p, n The specified Bytes.
/// @return @a true if the Bytes are equal, @a false otherwise.
Ring2_Boolean
Ring2_ByteBuffer_compareBytes
  (
    Ring2_ByteBuffer const* self,
    char const* p,
    size_t n
  );


#endif // RING2_LIBRARY_BYTEBUFFER_H_INCLUDED
