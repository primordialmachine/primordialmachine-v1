// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/CallArguments.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

/// @brief Functionality to access call argument lists.

#if !defined(RING2_LIBRARY_CALLARGUMENTS_H_INCLUDED)
#define RING2_LIBRARY_CALLARGUMENTS_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/CallArguments.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

Ring1_CheckReturn() Ring2_Boolean
Ring2_CallArguments_getBooleanArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Ring1_CheckReturn() Ring2_Integer
Ring2_CallArguments_getIntegerArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Ring1_CheckReturn() Ring2_Real32
Ring2_CallArguments_getReal32Argument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Ring1_CheckReturn() Ring2_Real64
Ring2_CallArguments_getReal64Argument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );

Ring1_CheckReturn() Ring2_String *
Ring2_CallArguments_getStringArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  );


/// @brief Validate the argument and return a pointer to the object.
/// @param numberOfArguments, arguments The arguments.
/// @param argumentIndex The index of the argument.
/// @param type The type the argument must be a subtype of.
Ring1_CheckReturn() Machine_Object *
Ring2_CallArguments_getObjectArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t argumentIndex,
    Machine_Type* t
  );

#endif // RING2_LIBRARY_CALLARGUMENTS_H_INCLUDED
