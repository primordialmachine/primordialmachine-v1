#if !defined(RING1_INTRINSIC_ADD_X86_ADD_S32_H_INCLUDED)
#define RING1_INTRINSIC_ADD_X86_ADD_S32_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Intrinsic/Add/Configuration.h"
#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Add_X86_add_s32
  (
    int32_t x,
    int32_t y,
    int32_t *z
  );

#endif

#endif // RING1_INTRINSIC_ADD_X86_ADD_S32_H_INCLUDED
