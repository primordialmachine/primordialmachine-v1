#if !defined(MACHINE_RUNTIME_BYTEBUFFER_H_INCLUDED)
#define MACHINE_RUNTIME_BYTEBUFFER_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "./../Machine.h"


MACHINE_DECLARE_CLASSTYPE(Machine_ByteBuffer)

/// @brief Create a Byte buffer.
/// @return The Byte buffer.
Machine_ByteBuffer* Machine_ByteBuffer_create();

/// @brief Append Bytes to this Byte buffer.
/// @param self This Byte bufffer
/// @param p, n The Bytes.
void Machine_ByteBuffer_appendBytes(Machine_ByteBuffer* self, const char* p, size_t n);

/// @brief Clear this Byte buffer.
/// @param self This Byte buffer.
void Machine_ByteBuffer_clear(Machine_ByteBuffer* self);

/// @brief Get a pointer to the Byte of this Byte buffer.
/// @param self This Byte buffer.
/// @return A pointer to the Byte of this Byte buffer.
const char* Machine_ByteBuffer_getBytes(const Machine_ByteBuffer* self);

/// @brief Get the number of Bytes of this Byte buffer.
/// @param self This Byte buffer.
/// @return The number of Bytes of this Byte buffer.
size_t Machine_ByteBuffer_getNumberOfBytes(const Machine_ByteBuffer* self);


#endif // MACHINE_RUNTIME_BYTEBUFFER_H_INCLUDED
