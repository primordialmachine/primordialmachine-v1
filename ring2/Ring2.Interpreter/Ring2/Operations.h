// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_H_INCLUDED)
#define RING2_OPERATIONS_H_INCLUDED

#include "Ring2/Configuration.h"
#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

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

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

  #include "Ring2/Operations/Boolean.h"

#endif // Ring2_Configuration_withBoolean

#if defined(Ring2_Configuration_withForeignFunction) && 1 == Ring2_Configuration_withForeignFunction

  #include "Ring2/Operations/ForeignFunction.h"

#endif // Ring2_Configuration_withForeignFunction

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

  #include "Ring2/Operations/Integer.h"

#endif // Ring2_Configuration_withInteger

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

  #include "Ring2/Operations/Real32.h"
  #include "Ring2/Operations/Real64.h"

#endif // Ring2_Configuration_withReal

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

  #include "Ring2/Operations/Void.h"

#endif // Ring2_Configuration_withVoid

#endif // RING2_OPERATIONS_H_INCLUDED
