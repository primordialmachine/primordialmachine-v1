#if !defined(RING1_INTRINSIC_ADD_X64_ADD_U64_H_INCLUDED)
#define RING1_INTRINSIC_ADD_X64_ADD_U64_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Add_X64_add_u64
  (
    uint64_t x,
    uint64_t y,
    uint64_t* z
  );

#endif

#endif // RING1_INTRINSIC_ADD_X64_ADD_U64_H_INCLUDED
