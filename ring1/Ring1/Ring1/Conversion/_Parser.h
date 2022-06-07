#if !defined(RING1_CONVERSION__PARSER_H_INCLUDED)
#define RING1_CONVERSION__PARSER_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Intrinsic/Inline.h"
#include "Ring1/Result.h"
#include <stdbool.h>
#include <stddef.h>

Ring1_Intrinsic_Inline()  Ring1_Intrinsic_CheckReturn() bool
isString
  (
    char const** new,
    char const* current,
    char const* start,
    char const* end,
    char const* p,
    size_t n
  )
{
  for (size_t i = 0; i < n; ++i) {
    if (current == end || p[i] != *current) {
      if (new)
        *new = current;
      return false;
    }
    current++;
  }
  if (new)
    *new = current;
  return true;
}

Ring1_Intrinsic_Inline() Ring1_Intrinsic_CheckReturn() bool
isDigit
  (
    char const** new,
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    if (new)
      *new = current;
    return false;
  }
  if ('0' <= (*current) && (*current) <= '9') {
    current++;
    if (new)
      *new = current;
    return true;
  } else {
    *new = current;
    return false;
  }
}

#endif // RING1_CONVERSION__PARSER_H_INCLUDED
