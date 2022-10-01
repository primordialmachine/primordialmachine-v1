// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/Deprecated.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_DEPRECATED_H_INCLUDED)
#define RING1_INTRINSIC_DEPRECATED_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

// https://documentation.primordialmachine.com/api/ring1-library/intrinsic-library/Ring1_Intrinsic_Deprecated
#if defined(__GNUC__)
  #define Ring1_Intrinsic_Deprecated()
#elif defined(_MSC_VER)
  #define Ring1_Intrinsic_Deprecated() __declspec(deprecated)
#else
  #error("environment not supported")
#endif

#define Ring1_Deprecated() Ring1_Intrinsic_Deprecated()

#endif // RING1_INTRINSIC_DEPRECATED_H_INCLUDED
