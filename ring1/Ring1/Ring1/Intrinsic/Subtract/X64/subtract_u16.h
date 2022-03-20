#if !defined(RING1_INTRINSIC_SUBTRACT_X64_SUBTRACT_U16_H_INCLUDED)
#define RING1_INTRINSIC_SUBTRACT_X64_SUBTRACT_U16_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Intrinsic/Subtract/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Subtract_X64_subtract_u16
  (
    uint16_t x,
    uint16_t y,
    uint16_t* z
  );

#endif

#endif // RING1_INTRINSIC_SUBTRACT_X64_SUBTRACT_U16_H_INCLUDED
