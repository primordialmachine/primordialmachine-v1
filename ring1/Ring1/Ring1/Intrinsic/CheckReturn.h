// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CheckReturn.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CHECKRETURN_H_INCLUDED)
#define RING1_INTRINSIC_CHECKRETURN_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

// https://preview.primordialmachine.com/ring1-library/intrinsic-library/Ring1_CheckReturn
#if defined(__GNUC__)
  #define Ring1_CheckReturn() [[nodiscard]]
#elif defined(_MSC_VER)
  #include <sal.h>
  #define Ring1_CheckReturn() _Check_return_
#else
  #error("environment not supported")
#endif

#endif // RING1_INTRINSIC_CHECKRETURN_H_INCLUDED