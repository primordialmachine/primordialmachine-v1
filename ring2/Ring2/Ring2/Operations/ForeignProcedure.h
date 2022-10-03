// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/ForeignProcedure.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_FOREIGNPROCEDURE_H_INCLUDED)
#define RING2_OPERATIONS_FOREIGNPROCEDURE_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Operations/ForeignProcedure.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

#include "Ring2/Context.h"
#include "Ring2/Types.h"

#endif // Ring2_Configuration_withForeignProcedure

#endif // RING2_OPERATIONS_FOREIGNFUNCTION_H_INCLUDED
