// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/isPowerOfTwo.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/isPowerOfTwo.h"

#include "Ring1/Status.h"

#define Implementation_sx(typeName, typeSuffix, unsignedTypeName, unsignedTypeSuffix) \
  Ring1_Result Ring1_Intrinsic_isPowerOfTwo_ ##typeSuffix(bool* result, typeName x) { \
    return Ring1_Intrinsic_isPowerOfTwo_##unsignedTypeSuffix(result, (unsignedTypeName)x); \
  }

Implementation_sx(int8_t, s8, uint8_t, u8);

Implementation_sx(int16_t, s16, uint16_t, u16);

Implementation_sx(int32_t, s32, uint32_t, u32);

Implementation_sx(int64_t, s64, uint64_t, u64);

#undef Implementation_sx

#define Implementation_ux(typeName, typeSuffix) \
  Ring1_Result Ring1_Intrinsic_isPowerOfTwo_##typeSuffix(bool* result, typeName x) { \
    if (NULL == result) { \
      Ring1_Status_set(Ring1_Status_InvalidArgument); \
      return Ring1_Result_Failure; \
    } \
    *result = (x != 0 && (x & (x - 1)) == 0); \
    return Ring1_Result_Success; \
  }

Implementation_ux(uint8_t, u8)

Implementation_ux(uint16_t, u16)

Implementation_ux(uint32_t, u32)

Implementation_ux(uint64_t, u64)

Implementation_ux(size_t, sz)

#undef Implementation_ux
