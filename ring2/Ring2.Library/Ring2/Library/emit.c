// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/emit.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/emit.h"
#undef RING2_LIBRARY_PRIVATE

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/StringExtensions.h"
#undef RING2_LIBRARY_PRIVATE
#include <stdarg.h>
#include <stdio.h>

void
Ring2_emitf
  (
    Ring2_Context* context,
    Ring2_String* format,
    ...
  )
{
  Ring2_JumpTarget jumpTarget;
  va_list arguments;
  va_start(arguments, format);
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_emitv(context, format, arguments);
    Ring2_popJumpTarget();
    va_end(arguments);
  } else {
    Ring2_popJumpTarget();
    Ring2_jump();
    va_end(arguments);
  }
}

void
Ring2_emitv
  (
    Ring2_Context* context,
    Ring2_String* format,
    va_list arguments
  )
{
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_String* string = Ring2_String_printv(context, format, arguments);
    fwrite(Ring2_String_getBytes(string), sizeof(char),
           (size_t)Ring2_String_getNumberOfBytes(string), stdout);
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    Ring2_jump();
  }
}
