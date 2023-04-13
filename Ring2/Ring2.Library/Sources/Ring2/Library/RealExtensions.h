// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/RealExtensions.h
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_REALEXTENSIONS_H_INCLUDED)
#define RING2_LIBRARY_REALEXTENSIONS_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("do not include `Ring2/Library/RealExtensions.h` directly. Instead, include `Ring2/Library/_Include.h`.")
#endif

#include "Ring2/_Include.h"

Ring1_Inline() Ring1_NoDiscardReturn() Ring2_Real32
Ring2_Real32_greatest
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x > y ? x : y; }

Ring1_Inline() Ring1_NoDiscardReturn() Ring2_Real32
Ring2_Real32_least
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x < y ? x : y; }

#endif // RING2_LIBRARY_REALEXTENSIONS_H_INCLUDED
