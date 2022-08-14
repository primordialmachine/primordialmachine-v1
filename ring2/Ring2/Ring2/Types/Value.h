// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Value.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_VALUE_H_INCLUDED)
#define RING2_TYPES_VALUE_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/Value.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Types.h"

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  #define Ring2_Value_Tag_Array (1)
#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  #define Ring2_Value_Tag_Boolean (2)
#endif

#if defined(Ring2_Configuration_withForeignFunction) && 1 == Ring2_Configuration_withForeignFunction
  #define Ring2_Value_Tag_ForeignFunction (3)
#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  #define Ring2_Value_Tag_Integer (4)
#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  #define Ring2_Value_Tag_Object (5)
#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  #define Ring2_Value_Tag_Real32 (6)
  #define Ring2_Value_Tag_Real64 (7)
#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  #define Ring2_Value_Tag_String (8)
#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  #define Ring2_Value_Tag_Void (9)
#endif

#endif // RING2_TYPES_VALUE_H_INCLUDED
