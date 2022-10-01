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

/// The version of the Ring2.Library.StringBuffer type implementation.
#define RING2_LIBRARY_STRINGBUFFER_VERSION (2)

/// @brief A Byte buffer.
MACHINE_DECLARE_CLASSTYPE(Machine_StringBuffer)

void
Machine_StringBuffer_construct
  (
    Machine_StringBuffer *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a string buffer.
/// @return The string buffer.
Machine_StringBuffer*
Machine_StringBuffer_create
  (
  );

/// @brief Append a Byte to this string buffer.
/// @param self This string buffer.
/// @param byte The Byte.
void
Machine_StringBuffer_appendByte
  (
    Machine_StringBuffer* self,
    char byte
  );

/// @brief Append Bytes to this string buffer.
/// @param self This string buffer.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes.
void
Machine_StringBuffer_appendBytes
  (
    Machine_StringBuffer* self,
    char const* bytes,
    size_t numberOfBytes
  );

/// @brief Append a string to this stirng buffer.
/// @param self This string buffer.
/// @param string The string.
void
Machine_StringBuffer_appendString
  (
    Machine_StringBuffer* self,
    Ring2_String* string
  );

/// @brief Clear this string buffer.
/// @param self This string buffer.
void
Machine_StringBuffer_clear
  (
    Machine_StringBuffer* self
  );

/// @brief Get the Bytes in this string buffer.
/// @param self This string buffer.
/// @return A pointer to an array of Bytes.
/// The array pointed
/// - must not be modified and
/// - is valid as long as this string buffer exists and is not modified.
const char*
Machine_StringBuffer_getBytes
  (
    Machine_StringBuffer* self
  );

/// @brief Get the number of Bytes in this string buffer.
/// @param self This string buffer.
size_t
Machine_StringBuffer_getNumberOfBytes
  (
    Machine_StringBuffer* self
  );

#endif // RING2_LIBRARY_STRINGBUFFER_H_INCLUDED
