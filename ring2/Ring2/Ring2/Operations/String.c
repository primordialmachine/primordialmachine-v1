// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/String.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/String.h"

#include "Ring1/Status.h"
#include "Ring1/Memory.h"
#include "Ring2/JumpTarget.h"

static int
compareBytes
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  )
{
  int temporary;
  Ring1_Memory_compare(&temporary,
                       Ring2_String_getBytes(context, x),
                       Ring2_String_getNumberOfBytes(context, x),
                       Ring2_String_getBytes(context, y),
                       Ring2_String_getNumberOfBytes(context, y),
                       Ring1_Memory_Compare_Lexicographic);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isEqualTo
  (
    Ring2_Context *context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isNotEqualTo
  (
    Ring2_Context *context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return x != y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isLowerThan
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) < 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) <= 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) > 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) >= 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_startWith
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  )
{
  size_t n = Ring2_String_getNumberOfBytes(context, x),
         m = Ring2_String_getNumberOfBytes(context, y);
  // empty string is a prefix of any string.
  if (!m)
    return true;
  // x can not start with y if y is longer than x.
  if (m > n)
    return false;
  int temporary;
  Ring1_Memory_compare(&temporary,
                       Ring2_String_getBytes(context, y),
                       (size_t)m,
                       Ring2_String_getBytes(context, x),
                       (size_t)m,
                       Ring1_Memory_Compare_Lexicographic);
  return !temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_endsWith
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  )
{
  size_t n = Ring2_String_getNumberOfBytes(context, x),
         m = Ring2_String_getNumberOfBytes(context, y);
  // empty string is a suffix of any string.
  if (!m)
    return true;
  // y can not be a suffix of x if y is longer than x.
  if (m > n)
    return false;
  int temporary;
  Ring1_Memory_compare(&temporary,
                       Ring2_String_getBytes(context, x) + (n - m),
                       (size_t)m,
                       Ring2_String_getBytes(context, y),
                       (size_t)m,
                       Ring1_Memory_Compare_Lexicographic);
  return !temporary;
}

Ring1_CheckReturn() Ring2_Integer
Ring2_String_firstOccurrenceOf
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  )
{
  char const *p = Ring2_String_getBytes(context, x),
             *q = Ring2_String_getBytes(context, y);
  int64_t n = Ring2_String_getNumberOfBytes(context, x),
          m = Ring2_String_getNumberOfBytes(context, y);
  if (m == 0)
    return 0;
  if (m > n)
    return -1;
  int64_t max = n - m;
  for (int64_t i = 0; i <= max; ++i) {
    if (p[i] == q[0]) {
      bool equal = true;
      for (int64_t j = 0, k = m; j < k; ++j) {
        if (p[i + j] != q[j]) {
          equal = false;
        }
      }
      if (equal)
        return i;
    }
  }
  return -1;
}

Ring1_CheckReturn() Ring2_String*
Ring2_String_substring
  (
    Ring2_Context* context,
    Ring2_String const* x,
    int64_t i,
    int64_t n
  )
{
  if (i < 0 || n < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (INT64_MAX - i < n) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (i + n > Ring2_String_getNumberOfBytes(context, x)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return Ring2_String_create(Ring2_Context_get(), Ring2_String_getBytes(context, x) + i, n);
}

