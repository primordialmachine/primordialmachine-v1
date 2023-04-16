// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/CommandLine.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COMMANDLINE_H_INCLUDED)
#define RING2_LIBRARY_COMMANDLINE_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("do not include `Ring2/Library/CommandLine.h` directly. Instead, include `Ring2/Library/_Include.h`.")
#endif

#include "Ring2/_Include.h"

/// @ffi
MACHINE_DECLARE_CLASSTYPE(Ring2_CommandLine_Argument)

struct Ring2_CommandLine_Argument_Class {
  Machine_Object_Class _parent;
};

struct Ring2_CommandLine_Argument {
  Machine_Object _parent;
  void* pimpl;
};

void
Ring2_CommandLine_Argument_construct
  (
    Ring2_CommandLine_Argument *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @ffi
/// @return A pointer to the string if the argument has a name, a null pointer otherwise.
Ring1_CheckReturn() Ring2_String *
Ring2_CommandLine_Argument_getName
  (
    Ring2_CommandLine_Argument* argument
  );

/// @ffi
/// @return A pointer to the string if the argument has a value, a null pointer otherwise.
Ring1_CheckReturn() Ring2_String *
Ring2_CommandLine_Argument_getValue
  (
    Ring2_CommandLine_Argument* argument
  );

/// @ffi
MACHINE_DECLARE_CLASSTYPE(Ring2_CommandLine_ArgumentList)

struct Ring2_CommandLine_ArgumentList_Class {
  Machine_Object_Class _parent;
};

struct Ring2_CommandLine_ArgumentList {
  Machine_Object _parent;
  void* pimpl;
};

void
Ring2_CommandLine_ArgumentList_construct
  (
    Ring2_CommandLine_ArgumentList *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @ffi
Ring1_CheckReturn() Ring2_CommandLine_ArgumentList*
Ring2_CommandLine_ArgumentList_create
  (
    int argc,
    const char** argv
  );

/// @ffi
/// @param context The context.
/// @param argumentList The argument list.
Ring1_CheckReturn() Ring2_CommandLine_Argument*
Ring2_CommandLine_ArgumentList_getAt
  (
    Ring2_CommandLine_ArgumentList* self,
    int64_t index
  );

/// @ffi
/// @brief Get the size of an argument list.
/// @param context The context.
/// @param argumentList The argument list.
/// @return The size of an argument list.
Ring1_CheckReturn() int64_t
Ring2_CommandLine_ArgumentList_getSize
  (
    Ring2_CommandLine_ArgumentList* self
  );

/// @ffi
/// @brief Remove the argument at the specified index.
/// @param context The context.
/// @param self The argument list.
/// @param index The index of the argument.
void
Ring2_CommandLine_ArgumentList_removeAt
  (
    Ring2_CommandLine_ArgumentList *self,
    int64_t index
  );

#endif // RING2_LIBRARY_COMMANDLINE_H_INCLUDED
