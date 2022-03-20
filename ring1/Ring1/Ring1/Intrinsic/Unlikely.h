// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Unlikely.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_UNLIKELY_H_INCLUDED)
#define RING1_INTRINSIC_UNLIKELY_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

/// @brief Expression annotation indicating an expression is unlikely to evaluate to logically true.
/// @param expression The expression.
#define Ring1_Intrinsic_Unlikely(expression) (expression)

#if defined(Ring1_Intrinsic_WithDeprecations) && 1 == Ring1_Intrinsic_WithDeprecations
  #define Ring1_Unlikely(expression) Ring1_Intrinsic_Unlikely(expression)
#endif

#endif // RING1_INTRINSIC_UNLIKELY_H_INCLUDED
