#if !defined(RING1_INTRINSIC_SUBTRACT_WINAPI_SUBTRACT_U32_H_INCLUDED)
#define RING1_INTRINSIC_SUBTRACT_WINAPI_SUBTRACT_U32_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Intrinsic/Subtract/Configuration.h"
#include <inttypes.h>

#if defined(RING1_INTRINSIC_SUBTRACT_CONFIGURATION_WITHWINAPI) &&              \
  1 == RING1_INTRINSIC_SUBTRACT_CONFIGURATION_WITHWINAPI

char
Ring1_Intrinsic_Subtract_Winapi_subtract_u32
  (
    uint32_t x,
    uint32_t y,
    uint32_t* z
  );

#endif

#endif // RING1_INTRINSIC_SUBTRACT_WINAPI_SUBTRACT_U32_H_INCLUDED
