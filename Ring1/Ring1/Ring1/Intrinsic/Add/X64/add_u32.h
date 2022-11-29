#if !defined(RING1_INTRINSIC_ADD_X64_ADD_U32_H_INCLUDED)
#define RING1_INTRINSIC_ADD_X64_ADD_U32_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Add_X64_add_u32
  (
    uint32_t x,
    uint32_t y,
    uint32_t* z
  );

#endif

#endif // RING1_INTRINSIC_ADD_X64_ADD_U32_H_INCLUDED
