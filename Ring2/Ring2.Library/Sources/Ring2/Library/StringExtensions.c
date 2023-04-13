// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/StringExtensions.c
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/StringExtensions.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/All/_Include.h"
#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"
#include <stdarg.h>
#include <stdio.h>


Ring1_CheckReturn() Ring2_String*
Ring2_String_printv
  (
    Ring2_Context* context,
    Ring2_String* format,
    va_list arguments
  )
{
  Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create(context);
  char const* start = Ring2_String_getBytes(format),
            * end = Ring2_String_getBytes(format)
                  + Ring2_String_getNumberOfBytes(format);
  char const* current = start;
  while (start != end)
  {
    while (current != end && *current != '%')
    {
      current++;
    }
    if (current - start > 0)
    {
      Ring2_StringBuffer_appendBytes(stringBuffer, start, current - start);
    }
    if (current == end)
    {
      break;
    }
    start = current;
    if (*current == '%')
    {
      current++;
      if (current == end)
      {
        fprintf(stderr, "invalid format string\n");
        Ring1_Status_set(Ring1_Status_InvalidSyntactics);
        Ring2_jump();
      }
      switch (*current)
      {
      case 'b':
      {
        Ring2_Boolean v = va_arg(arguments, Ring2_Boolean);
        Ring2_String* s = Ring2_Boolean_toString(context, v);
        Ring2_StringBuffer_appendString(stringBuffer, s);
        current++;
      } break;
      case 's':
      {
        Ring2_String* s = va_arg(arguments, Ring2_String*);
        Ring2_StringBuffer_appendString(stringBuffer, s);
        current++;
      } break;
      case 'i':
      {
        Ring2_Integer v = va_arg(arguments, Ring2_Integer);
        Ring2_String* s = Ring2_Integer_toString(context, v);
        Ring2_StringBuffer_appendString(stringBuffer, s);
        current++;
      } break;
      case 'r32':
      {
        Ring2_Real32 v = va_arg(arguments, Ring2_Real32);
        Ring2_String* s = Ring2_Real32_toString(context, v);
        Ring2_StringBuffer_appendString(stringBuffer, s);
        current++;
      } break;
      case 'r64':
      {
        Ring2_Real64 v = va_arg(arguments, Ring2_Real64);
        Ring2_String* s = Ring2_Real64_toString(context, v);
        Ring2_StringBuffer_appendString(stringBuffer, s);
        current++;
      } break;
      case 'v':
      {
        Ring2_String* s = Ring2_Void_toString(context, Ring2_Void_Void);
        Ring2_StringBuffer_appendString(stringBuffer, s);
        current++;
      } break;
      default:
      {
        fprintf(stderr, "invalid format string\n");
        Ring1_Status_set(Ring1_Status_InvalidSyntactics);
        Ring2_jump();
      } break;
      }; // switch
      start = current;
    }
  }
  return Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, stringBuffer));
}

Ring1_CheckReturn() Ring2_String*
Ring2_String_printf
  (
    Ring2_Context *context,
    Ring2_String* format,
    ...
  )
{
  Ring2_JumpTarget jumpTarget;
  va_list arguments;
  va_start(arguments, format);
  Ring2_pushJumpTarget(&jumpTarget);
  Ring2_String* string;
  if (!setjmp(jumpTarget.environment))
  {
    string = Ring2_String_printv(context, format, arguments);
    Ring2_popJumpTarget();
    va_end(arguments);
  }
  else
  {
    Ring2_popJumpTarget();
    va_end(arguments);
    Ring2_jump();
  }
  return string;
}

Ring1_CheckReturn() Ring2_String*
Ring2_String_fromC
  (
    bool includeZeroTerminator,
    const char* string
  )
{
  if (!string) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  size_t n = crt_strlen(string);
  return Ring2_String_create(string, includeZeroTerminator ? n + 1 : n);
}
