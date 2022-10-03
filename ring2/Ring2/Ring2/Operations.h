// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_H_INCLUDED)
#define RING2_OPERATIONS_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Operations.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


/// @brief Starts up the "operations" module.
/// @remarks Also starts up the "jump target" module and the "types" module.
Ring1_CheckReturn() Ring1_Result
Ring2_OperationsModule_startup
  (
  );

/// @brief Shuts down the "operations" module.
/// @remarks Also shuts down the "types" module and the "jump target" module.
void
Ring2_OperationsModule_shutdown
  (
  );

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

  #include "Ring2/Operations/Array.h"

#endif // Ring2_Configuration_withArray

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

  #include "Ring2/Operations/Boolean.h"

#endif // Ring2_Configuration_withBoolean

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

  #include "Ring2/Operations/ForeignProcedure.h"

#endif // Ring2_Configuration_withForeignProcedure

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

  #include "Ring2/Operations/Integer.h"

#endif // Ring2_Configuration_withInteger

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

  #include "Ring2/Operations/Object.h"

#endif // Ring2_Configuration_withObject

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

  #include "Ring2/Operations/Real32.h"
  #include "Ring2/Operations/Real64.h"

#endif // Ring2_Configuration_withReal

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

  #include "Ring2/Operations/String.h"

#endif // Ring2_Configuration_withString

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

  #include "Ring2/Operations/Void.h"

#endif // Ring2_Configuration_withVoid

#include "Ring2/Operations/Value.h"

#endif // RING2_OPERATIONS_H_INCLUDED
