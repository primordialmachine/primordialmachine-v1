/// @file Runtime/String.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_STRING_H_INCLUDED)
#define MACHINE_RUNTIME_STRING_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/String.h` directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/PrimitiveTypes.h"

/// C level representation of a string.
typedef struct Ring2_String Ring2_String;

/// @brief Create a string.
/// @param p, n The Bytes.
/// @return The string.
/// @error #Machine_Status_ArgumentNull @a p is a null pointer.
/// @error #Machine_Status_TooLong @a n exceeds a certain limit.
Ring2_String* Machine_String_create(char const* p, size_t n);

/// @brief Create a string.
/// @param p, n The Bytes.
/// @return The string.
/// @error #Machine_Status_ArgumentNull @a self is a null pointer.
/// @error #Machine_Status_ArgumentNull @a other is a null pointer.
/// @error #Machine_Status_TooLong The sum of the lengths of the strings exceeds a certain limit.
Ring2_String* Machine_String_concatenate(Ring2_String const* self, Ring2_String const* other);

/// @brief Get if this string is equal to another string.
/// @param self This string.
/// @param other The other string.
/// @return @a true if this string string is equal to the other string.
bool Machine_String_isEqualTo(Ring2_String const* self, Ring2_String const* other);

/// @brief Get the hash value of this string.
/// @param self This string.
/// @return The hash value of this string.
Ring2_Integer Machine_String_getHashValue(Ring2_String const* self);

/// @brief Get the Bytes of this string.
/// @param self A pointer to this string.
/// @return A pointer to the Bytes of this string.
/// @warning The pointer remains valid only as long as the string object is valid.
/// @warning The memory pointed to may not be modified.
char const* Machine_String_getBytes(Ring2_String const* self);

/// @brief Get the number of Bytes of this string.
/// @param self A pointer to this string.
/// @return The number of Bytes.
size_t Machine_String_getNumberOfBytes(Ring2_String const* self);

#endif // MACHINE_RUNTIME_STRING_H_INCLUDED
