// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/atomicDecrement.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/atomicDecrement.h"


#if defined(_MSC_VER)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#endif // _MSC_VER


#if defined(_MSC_VER)

int32_t
Ring1_Intrinsic_atomicDecrement_s32
  (
    volatile int32_t* variable
  )
{ return InterlockedDecrement(variable); }

#endif // _MSC_VER
