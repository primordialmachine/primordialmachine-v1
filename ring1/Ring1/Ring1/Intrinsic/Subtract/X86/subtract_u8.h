#if !defined(RING1_INTRINSIC_SUBTRACT_X86_SUBTRACT_U8_H_INCLUDED)
#define RING1_INTRINSIC_SUBTRACT_X86_SUBTRACT_U8_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Intrinsic/Subtract/Configuration.h"
#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Subtract_X86_subtract_u8
  (
    uint8_t x,
    uint8_t y,
    uint8_t *z
  );

#endif

#endif // RING1_INTRINSIC_SUBTRACT_X86_SUBTRACT_U8_H_INCLUDED
