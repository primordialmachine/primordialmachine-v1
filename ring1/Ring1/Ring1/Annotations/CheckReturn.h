// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/CheckReturn.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CHECKRETURN_H_INCLUDED)
#define RING1_INTRINSIC_CHECKRETURN_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

// Indicates that the result should not be used in a void context.
// https://primordialmachine.com/api/ring1-library/intrinsic-library/Ring1_NoDiscardResult
#if defined(__GNUC__)
  #define Ring1_NoDiscardResult() [[nodiscard]]
#elif defined(_MSC_VER)
  #include <sal.h>
  #define Ring1_NoDiscardResult() _Check_return_
#else
  #error("environment not supported")
#endif

// @deprecated
#define Ring1_CheckReturn() Ring1_NoDiscardResult()

#endif // RING1_INTRINSIC_CHECKRETURN_H_INCLUDED
