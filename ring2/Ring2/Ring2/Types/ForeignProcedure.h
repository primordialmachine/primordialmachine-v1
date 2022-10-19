// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/ForeignProcedure.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

#if !defined(RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED)
#define RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/ForeignProcedure.h` directly, include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

#include <stdint.h>

/// @brief The C-level representation of the <code>ForeignProcedure</code> type.
typedef void(Ring2_ForeignProcedure)(Ring2_Context* context,
                                     Ring2_Value *result,
                                     size_t numberOfArguments,
                                     Ring2_Value const* arguments);

#endif // Ring2_Configuration_withForeignProcedure

#endif // RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED
