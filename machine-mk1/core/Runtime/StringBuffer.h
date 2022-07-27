/// @file Runtime/StringBuffer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_STRINGBUFFER_H_INCLUDED)
#define MACHINE_RUNTIME_STRINGBUFFER_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/StringBuffer.h` directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Object/ClassType.h"
typedef struct Ring2_String Ring2_String;

/// @brief A string buffer.
/// You can append/prepend/insert strings.
/// To convert the contents of a string buffer to a string, call Machine_Object_toString(Machine_Object const*) on the string buffer.
MACHINE_DECLARE_CLASSTYPE(Machine_StringBuffer)

/// @brief Create a string buffer.
/// @return The string buffer.
Machine_StringBuffer* Machine_StringBuffer_create();

/// @brief Append Bytes to this string buffer.
/// @param self This string buffer.
/// @param p, n The Bytes.
void Machine_StringBuffer_appendBytes(Machine_StringBuffer* self, char const *p, size_t n);

/// @brief Append a string to this string buffer.
/// @param self This string buffer.
/// @param s the string.
void Machine_StringBuffer_appendString(Machine_StringBuffer* self, Ring2_String const* s);

/// @brief Prepend Bytes to the string buffer.
/// @param self This string buffer.
/// @param p, n The Bytes.
void Machine_StringBuffer_prependBytes(Machine_StringBuffer* self, char const* p, size_t n);

/// @brief Prepend a string to this string buffer.
/// @param self This string buffer.
/// @param s the string.
void Machine_StringBuffer_prependString(Machine_StringBuffer* self, Ring2_String const* s);

/// @brief Insert Bytes to this string buffer.
/// @param self This string buffer.
/// @param i The index at which to insert the Bytes.
/// @param p, n The Bytes.
void Machine_StringBuffer_insertBytesAt(Machine_StringBuffer* self, size_t i, const char* p,
                                        size_t n);

/// @brief Clear this string buffer.
/// @param self This string buffer.
void Machine_StringBuffer_clear(Machine_StringBuffer* self);

#endif // MACHINE_RUNTIME_STRINGBUFFER_H_INCLUDED
