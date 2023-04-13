#if !defined(RING1_CONVERSION__PARSER_H_INCLUDED)
#define RING1_CONVERSION__PARSER_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stdbool.h>
#include <stddef.h>

Ring1_Inline() Ring1_NoDiscardReturn() bool
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

Ring1_Inline() Ring1_NoDiscardReturn() bool
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
    if (new)
      *new = current;
    return false;
  }
}

#endif // RING1_CONVERSION__PARSER_H_INCLUDED
