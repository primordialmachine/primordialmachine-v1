// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArgumentsUtilities.h
/// @copyright Copyright (c) 2021-200 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

/// @brief Functionality to access argument lists.

#if !defined(RING2_LIBRARIES_ARGUMENTSUTILITIES_H_INCLUDED)
#define RING2_LIBRARIES_ARGUMENTSUTILITIES_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ArgumentsUtilities.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

Ring2_Boolean
Machine_Extensions_getBooleanArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Ring2_Integer
Machine_Extensions_getIntegerArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Ring2_String*
Machine_Extensions_getStringArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Machine_Object*
Machine_Extensions_getObjectArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i,
    Machine_ClassType* t
  );

#endif // RING2_LIBRARIES_ARGUMENTSUTILITIES_H_INCLUDED
