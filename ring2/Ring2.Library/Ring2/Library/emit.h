// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/emit.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_EMIT_H_INCLUDED)
#define RING2_LIBRARY_EMIT_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("do not include `Ring2/Library/emit.h` directly. Instead, include `Ring2/Library/_Include.h`.")
#endif

#include "Ring2/_Include.h"

/// @brief Emit a formatted string.
/// @param format The format string.
/// @param ... The arguments.
/// @remark
/// Below is a list of the supported format options.
/// - %b   a (Ring2_Boolean) object
/// - %r32 a (Ring2_Real32) object
/// - %r64 a (Ring2_Real64) object
/// - %i   a (Ring2_Integer) object
/// - %s   a (Ring2_String *) object
/// - %v   a (Ring2_Void) object
void
Ring2_emitf
  (
    Ring2_Context* context,
    Ring2_String*format,
    ...
  );

/// @brief Emit a formatted string.
/// @param format The format string.
/// @param arguments The arguments.
/// @see Ring2_emitf for a description of the format strings.
void
Ring2_emitv
  (
    Ring2_Context* context,
    Ring2_String* format,
    va_list arguments
  );

#endif // RING2_LIBRARY_EMIT_H_INCLUDED
