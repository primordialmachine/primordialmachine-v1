#if !defined(RING1_AP_PARSE_H_INCLUDED)
#define RING1_AP_PARSE_H_INCLUDED

#include "Ring1/Ap/ApNat.h"
#include "Ring1/Ap/ApInt.h"
#include "Ring1/Ap/ApReal.h"

Ring1_NoDiscardReturn() Ring1_Result
parseReal
  (
    char const *start,
    char const *end,
    Ring1_ApReal *real
  );

Ring1_NoDiscardReturn() Ring1_Result
parseInteger
  (
    char const *start,
    char const *end,
    Ring1_ApInt *integer
  );

Ring1_NoDiscardReturn() Ring1_Result
parseNatural
  (
    char const* start,
    char const* end,
    Ring1_ApNat* natural
  );

#endif // RING1_AP_PARSE_H_INCLUDED
