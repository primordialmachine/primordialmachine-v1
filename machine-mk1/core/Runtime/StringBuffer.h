#if !defined(MACHINE_RUNTIME_STRINGBUFFER_H_INCLUDED)
#define MACHINE_RUNTIME_STRINGBUFFER_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "./../Machine.h"


MACHINE_DECLARE_CLASSTYPE(Machine_StringBuffer)

/**
 * @brief Create a string buffer.
 * @return The string buffer.
 */
Machine_StringBuffer* Machine_StringBuffer_create();

/// @brief Append Bytes to this string buffer.
/// @param self This string buffer.
/// @param p, n The Bytes.
void Machine_StringBuffer_appendBytes(Machine_StringBuffer* self, const char *p, size_t n);

/// @brief Prepend Bytes to the string buffer.
/// @param self This string buffer.
/// @param p, n The Bytes.
void Machine_StringBuffer_prependBytes(Machine_StringBuffer* self, const char* p, size_t n);

/// @brief Insert Bytes to this string buffer.
/// @param self This string buffer.
/// @param i The index at which to insert the Bytes.
/// @param p, n The Bytes.
void Machine_StringBuffer_insertBytesAt(Machine_StringBuffer* self, size_t i, const char* p, size_t n);

/**
 * @brief Clear this string buffer.
 * @param self This string buffer.
 */
void Machine_StringBuffer_clear(Machine_StringBuffer* self);

/**
 * @brief Get the contents of this string buffer as a string.
 * @param self This string buffer.
 * @return The string.
 */
Machine_String* Machine_StringBuffer_toString(Machine_StringBuffer* self);


#endif // MACHINE_RUNTIME_STRINGBUFFER_H_INCLUDED
