// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/StringExtensions.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_STRINGEXTENSIONS_PRINT_H_INCLUDED)
#define RING2_LIBRARY_STRINGEXTENSIONS_PRINT_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("do not include `Ring2/Library/StringExtensions.h` directly. Instead, include `Ring2/Library/_Include.h`.")
#endif

#include "Ring2/_Include.h"

/// @brief Print a formatted string.
/// @param format the format string
/// @param ... the arguments
/// @remark
/// Below is a list of the supported format options.
/// - %b   a (Ring2_Boolean) object
/// - %r32 a (Ring2_Real32) object
/// - %r64 a (Ring2_Real64) object
/// - %i   a (Ring2_Integer) object
/// - %s   a pointer to a (Ring2_String *)
/// - %v   a (Ring2_Void) object
Ring1_CheckReturn() Ring2_String*
Ring2_String_printv
  (
    Ring2_Context* context,
    Ring2_String* format,
    va_list arguments
  );

Ring1_CheckReturn() Ring2_String*
Ring2_String_printf
  (
    Ring2_Context* context,
    Ring2_String* format,
    ...
  );

/// @brief Create a string from a C string.
/// @param p A pointer to the C string.
/// @return The string.
Ring1_CheckReturn() Ring2_String*
Ring2_String_fromC
  (
    const char* p
  );

#endif // RING2_LIBRARY_STRINGEXTENSIONS_PRINT_H_INCLUDED
