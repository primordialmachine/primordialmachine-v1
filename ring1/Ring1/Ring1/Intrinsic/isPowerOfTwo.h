// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/isPowerOfTwo.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_ISPOWEROFTWO_H_INCLUDED)
#define RING1_INTRINSIC_ISPOWEROFTWO_H_INCLUDED

#include <stdbool.h>
#include <inttypes.h>
#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_s8(bool* result, int8_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_s16(bool* result, int16_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_s32(bool* result, int32_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_s64(bool* result, int64_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_u8(bool *result, uint8_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_u16(bool *result, uint16_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_u32(bool *result, uint32_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_u64(bool *result, uint64_t x);

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_Intrinsic_isPowerOfTwo.html
Ring1_Result Ring1_Intrinsic_isPowerOfTwo_sz(bool *result, size_t x);

#endif // RING1_INSTRINSIC_ISPOWEROFTWO_H_INCLUDED
