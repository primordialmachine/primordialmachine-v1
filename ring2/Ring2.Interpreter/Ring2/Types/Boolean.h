// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Boolean.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_BOOLEAN_H_INCLUDED)
#define RING2_TYPES_BOOLEAN_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

#include <stdbool.h>

/// @brief The C-level representation of the "Boolean" type.
typedef bool Ring2_Boolean;

/// @brief Symbolic constant evaluating to the C-level representation of the "true" value.
#define Ring2_Boolean_True (true)

/// @brief Symbolic constant evaluating to the C-level representation of th "false" value.
#define Ring2_Boolean_False (false)

#endif // Ring2_Configuration_withBoolean

#endif // RING2_TYPES_BOOLEAN_H_INCLUDED
