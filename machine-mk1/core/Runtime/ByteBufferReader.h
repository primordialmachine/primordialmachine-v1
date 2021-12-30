#if !defined(MACHINE_BYTEBUFFERREADER_H_INCLUDED)
#define MACHINE_BYTEBUFFERREADER_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/ByteBuffer.h"

MACHINE_DECLARE_CLASSTYPE(Machine_ByteBufferReader)

void Machine_ByteBufferReader_construct(Machine_ByteBufferReader* self, size_t numberOfArguments,
                                        Machine_Value const* arguments);

/// @brief Create a Byte buffer reader.
/// @param byteBuffer The byte buffer.
/// @return The Byte buffer reader.
Machine_ByteBufferReader* Machine_ByteBufferReader_create(Machine_ByteBuffer* byteBuffer);

/// @brief Get the position.
/// @param self This Byte buffer reader.
/// @return The position.
size_t Machine_ByteBufferReader_getPosition(Machine_ByteBufferReader* self);

/// @brief Read up to @a n Bytes.
/// @param self This Byte buffer reader.
/// @param p A pointer to a buffer of at least @a n Bytes.
/// @param n The number of Bytes to read.
/// @param m A pointer to a variable. Receives the number of Bytes read.
void Machine_ByteBufferReader_read(Machine_ByteBufferReader* self, char* p, size_t n, size_t* m);

#endif // MACHINE_BYTEBUFFERREADER_H_INCLUDED
