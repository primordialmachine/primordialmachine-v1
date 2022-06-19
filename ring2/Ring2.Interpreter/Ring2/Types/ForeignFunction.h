// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/ForeignFunction.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_FOREIGNFUNCTION_H_INCLUDED)
#define RING2_TYPES_FOREIGNFUNCTION_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withForeignFunction) && 1 == Ring2_Configuration_withForeignFunction

#include "Ring2/Context.h"
#include <stdbool.h>

/// @brief The C-level representation of the "ForeignFunction" type.
typedef void (Ring2_ForeignFunction)(Ring2_Context *context);

#endif // Ring2_Configuration_withForeignFunction

#endif // RING2_TYPES_FOREIGNFUNCTION_H_INCLUDED
