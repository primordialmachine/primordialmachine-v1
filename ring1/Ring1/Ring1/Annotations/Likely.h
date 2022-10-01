// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/Likely.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_LIKELY_H_INCLUDED)
#define RING1_INTRINSIC_LIKELY_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

/// @brief Expression annotation indicating an expression is likely to evaluate to logically true.
/// @param expression The expression.
#define Ring1_Likely(expression) (expression)

#endif // RING1_INTRINSIC_LIKELY_H_INCLUDED
