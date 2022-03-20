#if !defined(RING1_INTRINSIC_SUBTRACT_X64_SUBTRACT_S64_H_INCLUDED)
#define RING1_INTRINSIC_SUBTRACT_X64_SUBTRACT_S64_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Intrinsic/Subtract/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Subtract_X64_subtract_s64
  (
    int64_t x,
    int64_t y,
    int64_t* z
  );

#endif

#endif // RING1_INTRINSIC_SUBTRACT_X64_SUBTRACT_S64_H_INCLUDED
