/// @file Runtime/ByteBuffer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_BYTEBUFFER_H_INCLUDED)
#define MACHINE_RUNTIME_BYTEBUFFER_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Object/ClassType.h"
#include "Runtime/PrimitiveTypes.h"

MACHINE_DECLARE_CLASSTYPE(Machine_ByteBuffer)

/// @brief Create a Byte buffer.
/// @return The Byte buffer.
Machine_ByteBuffer* Machine_ByteBuffer_create();

/// @brief Append specified Bytes to this Byte buffer.
/// @param self This Byte buffer.
/// @param p, n The specified Bytes.
void Machine_ByteBuffer_appendBytes(Machine_ByteBuffer* self, const char* p, size_t n);

/// @brief Prepend specified Bytes to this Byte buffer.
/// @param self This Byte buffer.
/// @param p, n The specified Bytes.
void Machine_ByteBuffer_prependBytes(Machine_ByteBuffer* self, const char* p, size_t n);

/// @brief Insert specified Bytes to this Byte buffer.
/// @param self This Byte buffer.
/// @param i The index at which to insert the Bytes.
/// @param p, n The specified Bytes.
void Machine_ByteBuffer_insertBytesAt(Machine_ByteBuffer* self, size_t i, const char* p, size_t n);

/// @brief Clear this Byte buffer.
/// @param self This Byte buffer.
void Machine_ByteBuffer_clear(Machine_ByteBuffer* self);

/// @brief Get a pointer to the Byte of this Byte buffer.
/// @param self This Byte buffer.
/// @return A pointer to the Byte of this Byte buffer.
char const* Machine_ByteBuffer_getBytes(Machine_ByteBuffer const* self);

/// @brief Get the number of Bytes of this Byte buffer.
/// @param self This Byte buffer.
/// @return The number of Bytes of this Byte buffer.
size_t Machine_ByteBuffer_getNumberOfBytes(Machine_ByteBuffer const* self);

/// @brief Compare the Bytes of this Byte buffer to the specified Bytes.
/// @param self This Byte buffer.
/// @param p, n The specified Bytes.
/// @return @a true if the Bytes are equal, @a false otherwise.
Machine_Boolean Machine_ByteBuffer_compareBytes(Machine_ByteBuffer const* self, char const* p,
                                                size_t n);

#endif // MACHINE_RUNTIME_BYTEBUFFER_H_INCLUDED
