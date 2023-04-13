/// @file Ring1/Crt/_Include.h
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING1_CRT__INCLUDE_H_INCLUDED)
#define RING1_CRT__INCLUDE_H_INCLUDED

#include "Ring1/Crt/atexit.h"
#include "Ring1/Crt/free.h"
#include "Ring1/Crt/malloc.h"
#include "Ring1/Crt/memcpy.h"
#include "Ring1/Crt/memset.h"
#include "Ring1/Crt/realloc.h"
#include "Ring1/Crt/setjmp.h"
#include "Ring1/Crt/strcmp.h"
#include "Ring1/Crt/strdup.h"
#include "Ring1/Crt/strlen.h"
#include "Ring1/Crt/strndup.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdbool.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The number of bits of the unsigned integer type size_t.
#if defined(_MSC_VER)
  #if defined( _WIN64)
    #define SIZE_BITS 64
  #else
    #define SIZE_BITS 32
  #endif
#else
  #error("environment not supported")
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(_MSC_VER)
  /// @brief The number of bits of the unsigned integer type uint64_t.
  #define UINT64_BITS 64
  /// @brief The number of bits of the unsigned integer type uint32_t.
  #define UINT32_BITS 32
  /// @brief The number of bits of the unsigned integer type uint16_t.
  #define UINT16_BITS 16
  /// @brief The number of bits of the unsigned integer type uint8_t.
  #define UINT8_BITS 8
#else
  #error("environment not supported")
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(_MSC_VER)
  /// @brief The number of bits of the unsigned integer type int64_t.
  #define INT64_BITS 64
  /// @brief The number of bits of the unsigned integer type int32_t.
  #define INT32_BITS 32
  /// @brief The number of bits of the unsigned integer type int16_t.
  #define INT16_BITS 16
  /// @brief The number of bits of the unsigned integer type int8_t.
  #define INT8_BITS 8
#else
  #error("environment not supported")
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief printf/scanf-style format specifier for size_t.
/// @remark This is necessary because of Redmon Retards' (aka Microsoft's) Visual C++.
#if defined(_MSC_VER)
  #define PRIuZ "Iu"
#else
  #define PRIuZ "zu"
#endif

#endif // RING1_CRT__INCLUDE_H_INCLUDED
