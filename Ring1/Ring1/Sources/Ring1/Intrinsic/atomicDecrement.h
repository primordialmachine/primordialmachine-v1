// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/atomicDecrement.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_ATOMICDECREMENT_H_INCLUDED)
#define RING1_INTRINSIC_ATOMICDECREMENT_H_INCLUDED


#if defined(_MSC_VER)
#include <stdint.h>
#endif // _MSC_VER


#if defined(_MSC_VER)

/// https://primordialmachine.com/api/ring1-library/intrinsic-library/Ring1_Intrinsic_atomicDecrement_s32
int32_t
Ring1_Intrinsic_atomicDecrement_s32
  (
    volatile int32_t* variable
  );

#endif // _MSC_VER


#endif // RING1_INTRINSIC_ATOMICDECREMENT_H_INCLUDED
