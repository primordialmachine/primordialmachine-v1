#if !defined(RING1_INTRINSIC_ADD_X64_ADD_U8_H_INCLUDED)
#define RING1_INTRINSIC_ADD_X64_ADD_U8_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Add_X64_add_u8
  (
    uint8_t x,
    uint8_t y,
    uint8_t *z
  );

#endif

#endif // RING1_INTRINSIC_ADD_X64_ADD_U8_H_INCLUDED
