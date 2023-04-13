#include "Ring1/Intrinsic/atomicCompareExchange.h"


#if defined(_MSC_VER)


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


#include <limits.h>


// We know that LONG and long are equivalent under MSVC.
// The following assert backs up this claim.
static_assert(sizeof(LONG) == sizeof(long), "LONG and long are not equivalent");

// We know that long and int are equivalent under MSVC.
// The following assert backs up this claim.
static_assert(sizeof(long) == sizeof(int) && LONG_MIN == INT_MIN && LONG_MAX == INT_MAX, "long and int are not interchangeable");

// We know that int32_t and int are equivalent under MSVC.
// The following assert backs up this claim.
static_assert(sizeof(int32_t) == sizeof(int) && INT32_MIN == INT_MIN && INT32_MAX == INT_MAX, "int32_t and int are not interchangeable");

// As LONG <=> long <=> int <=> int32_t, our use of InterlockedCompareExchange is correct.
#endif // _MSC_VER


#if defined(_MSC_VER)
int8_t
Mkx_Intrinsic_atomicCompareExchange_s8
  (
    volatile int8_t* variable,
    int8_t oldValue,
    int8_t newValue
  )
{ return oldValue == _InterlockedCompareExchange8(variable, newValue, oldValue); }
#endif // _MSC_VER


#if defined(_MSC_VER)
int16_t
Mkx_Intrinsic_atomicCompareExchange_s16
  (
    volatile int16_t* variable,
    int16_t oldValue,
    int16_t newValue
  )
{ return oldValue == _InterlockedCompareExchange16(variable, newValue, oldValue); }
#endif // _MSC_VER


#if defined(_MSC_VER)
int32_t
Mkx_Intrinsic_atomicCompareExchange_s32
  ( 
    volatile int32_t *variable,
    int32_t oldValue,
    int32_t newValue
  )
{ return oldValue == _InterlockedCompareExchange(variable, newValue, oldValue); }

#endif // _MSC_VER
