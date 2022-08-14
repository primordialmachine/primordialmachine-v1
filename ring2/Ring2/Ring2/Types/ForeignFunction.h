// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/ForeignFunction.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_FOREIGNFUNCTION_H_INCLUDED)
#define RING2_TYPES_FOREIGNFUNCTION_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/ForeignFunction.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withForeignFunction) && 1 == Ring2_Configuration_withForeignFunction

#include "Ring2/Context.h"
#include <stddef.h>
#include <stdbool.h>
typedef struct Machine_Value Machine_Value;
typedef struct Ring2_Context Ring2_Context;

/// @brief The C-level representation of the "ForeignFunction" type.
typedef void (Ring2_ForeignFunction)(Ring2_Context *context, Machine_Value *result, size_t numberOfArguments, Machine_Value const *arguments);

#endif // Ring2_Configuration_withForeignFunction

#endif // RING2_TYPES_FOREIGNFUNCTION_H_INCLUDED
