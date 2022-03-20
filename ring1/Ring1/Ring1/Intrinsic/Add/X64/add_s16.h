#if !defined(RING1_INTRINSIC_ADD_X86_ADD_S16_H_INCLUDED)
#define RING1_INTRINSIC_ADD_X86_ADD_S16_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Add_X64_add_s16
  (
    int16_t x,
    int16_t y,
    int16_t *z
  );

#endif

#endif // RING1_INTRINSIC_ADD_X86_ADD_S16_H_INCLUDED
