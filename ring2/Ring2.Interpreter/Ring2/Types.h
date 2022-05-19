// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_H_INCLUDED)
#define RING2_TYPES_H_INCLUDED

#include "Ring2/Configuration.h"
#include "Ring1/Result.h"

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

  #include "Ring2/Types/Boolean.h"

#endif // Ring2_Configuration_withBoolean

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

  #include "Ring2/Types/Integer.h"

#endif // Ring2_Configuration_withInteger

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

  #include "Ring2/Types/Real.h"

#endif // Ring2_Configuration_withReal

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

  #include "Ring2/Types/Void.h"

#endif // Ring2_Configuration_withVoid

#endif // RING2_TYPES_H_INCLUDED
