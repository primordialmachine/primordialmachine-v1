// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/FloatingPointTypes.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_FLOATINGPOINTTYPES_H_INCLUDED)
#define RING1_INTRINSIC_FLOATINGPOINTTYPES_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"
#include "Ring1/Result.h"
#include "Ring1/Intrinsic/CheckReturn.h"
#include <math.h>
#include <stdint.h>

#if defined(Ring1_Intrinsic_WithFp32) && 1 == Ring1_Intrinsic_WithFp32

#define Ring1_Intrinsic_Fp_Infinity_f32 INFINITY

#define Ring1_Intrinsic_Fp_NoNumber_f32 NAN

#define Ring1_Intrinsic_Fp_SignBits_f32 1

#define Ring1_Intrinsic_Fp_ExponentBits_f32 8

#define Ring1_Intrinsic_Fp_SignificantBits_f32 23

/// @brief Symbolic constant evaluating to a uint32_t value.
/// Masks the sign bit of the raw bits of a single-precision floating-point value (1 bit at index 31).
#define Ring1_Intrinsic_Fp_SignMask_f32 (UINT32_C(0x80000000))

/// @brief Symbolic constant evaluating to a uint32_t value.
/// Masks the exponent bits of the raw bits representation of a single-precision floating-point value (8 bits from index 30 to 23).
#define Ring1_Intrinsic_Fp_ExponentMask_f32 (UINT32_C(0x7F800000))

/// @brief Symbolic constant evaluating to an uint32_t value.
/// Masks the significant bits of the raw bits of a single-precision floating-point value (23 bits from index 22 to index 0).
#define Ring1_Intrinsic_Fp_SignificantMask_f32 (UINT32_C(0x007FFFFF))
                                           
/// @brief Symbolic constant evaluating to an uint32_t value.
/// Represents the raw bits of a single-precision floating point value representing the negative zero.
#define Ring1_Intrinsic_Fp_NegativeZero_f32 (UINT32_C(0x80000000))

/// @brief Symbolic constant evaluating to an uint32_t value.
/// Represents the raw bits of a single-precision floating point value representing the positive zero.
#define Ring1_Intrinsic_Fp_PositiveZero_f32 (UINT32_C(0x00000000))

#endif // Ring1_Fp_WithFp32

#if defined(Ring1_Intrinsic_WithFp64) && 1 == Ring1_Intrinsic_WithFp64

#define Ring1_Intrinsic_Fp_Infinity_f64 INFINITY

#define Ring1_Intrinsic_Fp_NoNumber_f64 NAN

#define Ring1_Intrinsic_Fp_SignBits_f64 1

#define Ring1_Intrinsic_Fp_ExponentBits_f64 11

#define Ring1_Intrinsic_Fp_SignificantBits_f64 52

/// @brief Symbolic constant evaluating to a uint32_t value.
/// Masks the sign bit of the raw bits representation of a double-precision floating-point value (1 bit at index 63).
#define Ring1_Intrinsic_Fp_SignMask_f64 (UINT64_C(0x8000000000000000))

/// @brief Symbolic constant evaluating to an uint64_t value.
/// Masks the exponent bits of the raw bits representation of a double-precision floating-point value (11 bits from index 63 to index 52). 
#define Ring1_Intrinsic_Fp_ExponentMask_f64 (UINT64_C(0x7FF0000000000000))

/// @brief Symbolic constant evaluating to an uint64_t value.
/// Masks the significant bits of the raw bits of a double-precision floating-point value (52 bits from index 51 to index 0).
#define Ring1_Intrinsic_Fp_SignificantMask_f64 (UINT64_C(0x000FFFFFFFFFFFFF))

/// @brief Symbolic constant evaluating to an uint64_t value.
/// Represents the raw bits of a single-precision floating point value representing the negative zero.
#define Ring1_Intrinsic_Fp_NegativeZero_f64 (UINT64_C(0x8000000000000000))

/// @brief Symbolic constant evaluating to an uint64_t value.
/// Represents the raw bits of a single-precision floating point value representing the positive zero.
#define Ring1_Intrinsic_Fp_PositiveZero_f64 (UINT64_C(0x0000000000000000))

#endif // Ring1_Fp_WithFp64

#if defined(Ring1_Intrinsic_WithFp32) && 1 == Ring1_Intrinsic_WithFp32

/// @brief Get the raw bits of a single-precision floating-point value.
/// @param x The single-precision floating-point value.
/// @return The raw bits of the single-precision floating-point value.
Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getRawBits_f32
  (
    uint32_t *result,
    float x
  );

/// @brief Get the bits of a single-precision floating-point value.
/// @param x The single-precision floating-point value.
/// @return The bits of the single-precision floating-point value.
/// @remark If x is no number, then the bits returned have the sign bit set to 1 and all payload bits set to zero.
/// @remark If x is negative zero, then this function returns the bits of the positive zero.
Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getBits_f32
  (
    uint32_t* result,
    float x
  );

#endif // Ring1_Intrinsic_WithFp32

#if defined(Ring1_Intrinsic_WithFp64) && 1 == Ring1_Intrinsic_WithFp64

/// @brief Get the raw bits of a double-precision floating-point value.
/// @param x The double-precision floating-point value.
/// @return The raw bits of the double-precision floating-point value.
Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getRawBits_f64
  (
    uint64_t* result,
    double x
  );

/// @brief Get the bits of a double-precision floating-point value.
/// @param x The double-precision floating-point value.
/// @return The bits of the double-precision floating-point value.
/// @remark If x is no number, then the bits returned have the sign bit set to 1 and all payload bits set to zero.
/// @remark If x is negative zero, then this function returns the bits of the positive zero.
Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getBits_f64
  (
    uint64_t *result,
    double x
  );

#endif // Ring1_Intrinsic_WithFp64

#endif // RING1_INTRINSIC_FLOATINGPOINTTYPES_H_INCLUDED
