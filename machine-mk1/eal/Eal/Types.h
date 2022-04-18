#if !defined(MACHINE_EAL_TYPES_H_INCLUDED)
#define MACHINE_EAL_TYPES_H_INCLUDED

#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Ring1/Intrinsic/Environment.h"
#include <stddef.h>
#include <stdbool.h>

/// @internal
#define SELF_CHECK(V, M) \
  static_assert(V > 0, #V " must be greater than 0"); \
  static_assert(V <= M, #V " must be smaller than or equal to " #M);

/// @brief The greatest power of two a size_t value can hold.
#define SIZE_GREATEST_POWER_OF_TWO (((size_t)1) << (SIZE_BITS-1))
SELF_CHECK(SIZE_GREATEST_POWER_OF_TWO, SIZE_MAX)

/// @brief The greatest power of two a uint64_t value can hold.
#define UINT64_GREATEST_POWER_OF_TWO (((uint64_t)1) << (UINT64_BITS-1))
SELF_CHECK(UINT64_GREATEST_POWER_OF_TWO, UINT64_MAX)

/// @brief The greatest power of two a uint32_t value can hold.
#define UINT32_GREATEST_POWER_OF_TWO (((uint32_t)1) << (UINT32_BITS-1))
SELF_CHECK(UINT32_GREATEST_POWER_OF_TWO, UINT32_MAX)

/// @brief The greatest power of two a uint16_t value can hold.
#define UINT16_GREATEST_POWER_OF_TWO (((uint16_t)1) << (UINT16_BITS-1))
SELF_CHECK(UINT16_GREATEST_POWER_OF_TWO, UINT16_MAX)

/// @brief The greatest power of two a uint8_t value can hold.
#define UINT8_GREATEST_POWER_OF_TWO (((uint8_t)1) << (UINT8_BITS-1))
SELF_CHECK(UINT8_GREATEST_POWER_OF_TWO, UINT8_MAX)

#undef SELF_CHECK

#endif // MACHINE_EAL_TYPES_H_INCLUDED
