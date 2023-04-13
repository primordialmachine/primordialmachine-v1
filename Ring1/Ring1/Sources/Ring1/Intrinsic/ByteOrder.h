// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/ByteOrder.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_BYTEORDER_H_INCLUDED)
#define RING1_INTRINSIC_BYTEORDER_H_INCLUDED

typedef enum Ring1_ByteOrder {
  Ring1_ByteOrder_LittleEndian,
  Ring1_ByteOrder_BigEndian,
} Ring1_ByteOrder;

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

#endif  // RING1_INTRINSIC_BYTEORDER_H_INCLUDED
