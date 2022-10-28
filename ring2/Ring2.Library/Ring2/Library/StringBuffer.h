// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/StringBuffer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_STRINGBUFFER_H_INCLUDED)
#define RING2_LIBRARY_STRINGBUFFER_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/StringBuffer.h` directly, include `Ring/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

/// @brief A Byte buffer.
MACHINE_DECLARE_CLASSTYPE(Ring2_StringBuffer)

void
Ring2_StringBuffer_construct
  (
    Ring2_StringBuffer *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a string buffer.
/// @return The string buffer.
Ring2_StringBuffer*
Ring2_StringBuffer_create
  (
  );

/// @brief Append a Byte to this string buffer.
/// @param self This string buffer.
/// @param byte The Byte.
void
Ring2_StringBuffer_appendByte
  (
    Ring2_StringBuffer* self,
    char byte
  );

/// @brief Append Bytes to this string buffer.
/// @param self This string buffer.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes.
void
Ring2_StringBuffer_appendBytes
  (
    Ring2_StringBuffer* self,
    char const* bytes,
    size_t numberOfBytes
  );

/// @brief Append a string to this stirng buffer.
/// @param self This string buffer.
/// @param string The string.
void
Ring2_StringBuffer_appendString
  (
    Ring2_StringBuffer* self,
    Ring2_String* string
  );

/// @brief Clear this string buffer.
/// @param self This string buffer.
void
Ring2_StringBuffer_clear
  (
    Ring2_StringBuffer* self
  );

/// @brief Get the Bytes in this string buffer.
/// @param self This string buffer.
/// @return A pointer to an array of Bytes.
/// The array pointed
/// - must not be modified and
/// - is valid as long as this string buffer exists and is not modified.
const char*
Ring2_StringBuffer_getBytes
  (
    Ring2_StringBuffer* self
  );

/// @brief Get the number of Bytes in this string buffer.
/// @param self This string buffer.
size_t
Ring2_StringBuffer_getNumberOfBytes
  (
    Ring2_StringBuffer* self
  );

#endif // RING2_LIBRARY_STRINGBUFFER_H_INCLUDED
