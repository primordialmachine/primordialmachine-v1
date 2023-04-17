// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/ByteOrder.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_BYTEORDER_H_INCLUDED)
#define RING1_INTRINSIC_BYTEORDER_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <inttypes.h>

typedef enum Ring1_ByteOrder {
  Ring1_ByteOrder_LittleEndian,
  Ring1_ByteOrder_BigEndian,
} Ring1_ByteOrder;

// Ring1_getByteOrder() returns the Byte Order of the target system.
// It is evaluated at compile time.
//
// A rnutime, one can determine the endianess of the target system by
// @code
// Ring1_NoDiscardReturn() Ring1_ByteOrder
// Ring1_getByteOrder()
//   (
//   )
// {
//   union {
//     int word;
//     char byte[sizeof(int)];
//   } test;
//   test.word = 1;
//   return test.byte[0] == 1 ? Ring1_ByteOrder_LittleEndian : Ring1_ByteOrder_BigEndian;
// }
// @endcode
#if defined(__GNUC__)
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define Ring1_getByteOrder() Ring1_ByteOrder_LittleEndian
  #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define Ring1_getByteOrder() Ring1_ByteOrder_BigEndian
  #else
    #error("environment not supported")
  #endif
#elif defined(_MSC_VER)
  #if defined(_M_IX86) || defined(_M_X64) || defined(_M_IA64) || defined(_M_ARM)
    #define Ring1_getByteOrder() Ring1_ByteOrder_LittleEndian
  #elif defined(_M_PPC)
    #define Ring1_getByteOrder() Ring1_ByteOrder_BigEndian
  #else
    #error("environment not supported")
  #endif
#else
  #error("environment not supported")
#endif


/// @brief Swap the Bytes of an <code>int16_t</code> value.
/// @param result A pointer to a <code>int16_t</code> variable.
/// @param self A <code>int16_t</code> value.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_s16
  (
    int16_t* result,
    int16_t self
  );

/// @brief Swap the Bytes of an <code>uint16_t</code> value.
/// @param result A pointer to a <code>uint16_t</code> variable.
/// @param self A <code>uint16_t</code> value.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_u16
  (
    uint16_t* result,
    uint16_t self
  );

/// @brief Swap the Bytes of a <code>int32_t</code> value.
/// @param result A pointer to a <code>int32_t</code> variable.
/// @param self A <code>int32_t</code> value.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_s32
  (
    int32_t* result,
    int32_t self
  );

/// @brief Swap the Bytes of a <code>uint32_t</code> value.
/// @param result A pointer to a <code>uint32_t</code> variable.
/// @param self A <code>uint32_t</code> value.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_u32
  (
    uint32_t* result,
    uint32_t self
  );

/// @brief Swap the Bytes of a <code>int64_t</code> value.
/// @param result A pointer to a <code>int64_t</code> variable.
/// @param self A <code>int64_t</code> value.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_s64
  (
    int64_t* result,
    int64_t self
  );

/// @brief Swap the Bytes of a <code>uint64_t</code> value.
/// @param result A pointer to a <code>uint64_t</code> variable.
/// @param self A <code>uint64_t</code> value.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_u64
  (
    uint64_t* result,
    uint64_t self
  );


#endif  // RING1_INTRINSIC_BYTEORDER_H_INCLUDED
