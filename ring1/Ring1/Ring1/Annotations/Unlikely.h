// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/Unlikely.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_UNLIKELY_H_INCLUDED)
#define RING1_INTRINSIC_UNLIKELY_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

/// @brief Expression annotation indicating an expression is unlikely to evaluate to logically true.
/// @param expression The expression.
#define Ring1_Unlikely(expression) (expression)

#endif // RING1_INTRINSIC_UNLIKELY_H_INCLUDED
