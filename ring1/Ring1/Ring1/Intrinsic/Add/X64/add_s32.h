#if !defined(RING1_INTRINSIC_ADD_X64_ADD_S32_H_INCLUDED)
#define RING1_INTRINSIC_ADD_X64_ADD_S32_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Add_X64_add_s32
  (
    int32_t x,
    int32_t y,
    int32_t *z
  );

#endif

#endif // RING1_INTRINSIC_ADD_X64_ADD_S32_H_INCLUDED
