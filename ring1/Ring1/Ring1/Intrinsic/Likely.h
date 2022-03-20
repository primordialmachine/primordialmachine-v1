// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Likely.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_LIKELY_H_INCLUDED)
#define RING1_INTRINSIC_LIKELY_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

/// @brief Expression annotation indicating an expression is likely to evaluate to logically true.
/// @param expression The expression.
#define Ring1_Intrinsic_Likely(expression) (expression)

#if defined(Ring1_Intrinsic_WithDeprecations) && 1 == Ring1_Intrinsic_WithDeprecations
  #define Ring1_Likely(expression) Ring1_Intrinsic_Likely(expression)
#endif

#endif // RING1_INTRINSIC_LIKELY_H_INCLUDED
