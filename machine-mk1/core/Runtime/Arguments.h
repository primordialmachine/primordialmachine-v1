/// @file Runtime/Arguments.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#if !defined(MACHINE_RUNTIME_ARGUMENTS_H_INCLUDED)
#define MACHINE_RUNTIME_ARGUMENTS_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Arguments.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring2/_Include.h"

Ring2_Integer Machine_Extensions_getBooleanArgument(size_t numberOfArguments,
                                                    Ring2_Value const* arguments, size_t i);

Ring2_Integer Machine_Extensions_getIntegerArgument(size_t numberOfArguments,
                                                    Ring2_Value const* arguments, size_t i);

Ring2_String* Machine_Extensions_getStringArgument(size_t numberOfArguments,
                                                   Ring2_Value const* arguments, size_t i);

Machine_Object* Machine_Extensions_getObjectArgument(size_t numberOfArguments,
                                                     Ring2_Value const* arguments, size_t i,
                                                     Machine_ClassType* t);

#endif // MACHINE_RUNTIME_ARGUMENTS_H_INCLUDED
