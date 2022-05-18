// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Integer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_INTEGER_H_INCLUDED)
#define RING2_TYPES_INTEGER_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

#include <inttypes.h>

/// @brief The C-level representation of the "Integer" type.
typedef int64_t Ring2_Integer;

/// @brief Symbolic constant evaluating to the C-level representation of the "Integer.Greatest" value.
#define Ring2_Integer_Greatest (INT64_MAX)

/// @brief Symbolic constant evaluating to the C-level representation of the "Integer.Least" value.
#define Ring2_Integer_Least (INT64_MIN)

#endif // Ring2_Configuration_withInteger

#endif // RING2_TYPES_INTEGER_H_INCLUDED
