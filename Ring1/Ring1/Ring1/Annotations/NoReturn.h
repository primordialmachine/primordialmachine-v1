// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/NoReturn.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_NORETURN_H_INCLUDED)
#define RING1_INTRINSIC_NORETURN_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

// https://documentation.primordialmachine.com/api/ring1-library/intrinsic-library/Ring1_NoReturn
#if defined(__GNUC__)
  #define Ring1_NoReturn() __attribute__((noreturn))
#elif defined(_MSC_VER)
  #define Ring1_NoReturn() __declspec(noreturn)
#else
  #error("unsupported compiler")
#endif

#endif // RING1_INTRINSIC_NORETURN_H_INCLUDED
