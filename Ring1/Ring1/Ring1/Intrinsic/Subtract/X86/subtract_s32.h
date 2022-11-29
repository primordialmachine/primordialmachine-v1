#if !defined(RING1_INTRINSIC_SUBTRACT_X86_SUBTRACT_S32_H_INCLUDED)
#define RING1_INTRINSIC_SUBTRACT_X86_SUBTRACT_S32_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Intrinsic/Subtract/Configuration.h"
#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Subtract_X86_subtract_s32
  (
    int32_t x,
    int32_t y,
    int32_t *z
  );

#endif

#endif // RING1_INTRINSIC_SUBTRACT_X86_SUBTRACT_S32_H_INCLUDED
