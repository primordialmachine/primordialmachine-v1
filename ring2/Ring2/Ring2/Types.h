// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_H_INCLUDED)
#define RING2_TYPES_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"
#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

/// @brief Starts up the "types" module.
/// @remarks Also starts up the "jump target" module.
Ring1_CheckReturn() Ring1_Result
Ring2_TypesModule_startup
  (
  );

/// @brief Shuts down the "types" module.
/// @remarks Also shuts down the "jump target" module.
void
Ring2_TypesModule_shutdown
  (
  );

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

  #include "Ring2/Types/Array.h"

#endif // Ring2_Configuration_withArray

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

  #include "Ring2/Types/Boolean.h"

#endif // Ring2_Configuration_withBoolean

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

  #include "Ring2/Types/ForeignProcedure.h"

#endif // Ring2_Configuration_withForeignProcedure

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

  #include "Ring2/Types/Integer.h"

#endif // Ring2_Configuration_withInteger

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

  #include "Ring2/Types/Object.h"

#endif // Ring2_Configuration_withObject

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

  #include "Ring2/Types/Real.h"

#endif // Ring2_Configuration_withReal

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

  #include "Ring2/Types/String.h"

#endif // Ring2_Configuration_withString

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

  #include "Ring2/Types/Void.h"

#endif // Ring2_Configuration_withVoid

#include "Ring2/Types/Value.h"

#endif // RING2_TYPES_H_INCLUDED
