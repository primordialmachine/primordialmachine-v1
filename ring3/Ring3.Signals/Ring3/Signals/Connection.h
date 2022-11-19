/// @file Ring3/Signals/Connection.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_SIGNALS_CONNECTION_H_INCLUDED)
#define RING3_SIGNALS_CONNECTION_H_INCLUDED

#if !defined(RING3_SIGNALS_PRIVATE)
#error("Do not include `Ring3/Signals/Connection.h` file directly, include `Ring3/Signals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// C-level definition of a connection.
/// The HLL-level definition is
/// @code
/// class Ring3.Signals.Connection {
///   ...
///   construct(String name, Object context, ForeignProcedure callback)
///   ...
/// }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Machine_Signals_Connection)

struct Machine_Signals_Connection_Class {
  Machine_Object_Class parent;
};

struct Machine_Signals_Connection {
  Machine_Object parent;
  Ring2_String* name;
  Machine_Object* context;
  Ring2_ForeignProcedure* callback;
};

void
Machine_Signals_Connection_construct
  (
    Machine_Signals_Connection* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );

Ring1_CheckReturn() Machine_Signals_Connection*
Machine_Signals_Connection_create
  (
    Ring2_String *name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

#endif // RING3_SIGNALS_CONNECTION_H_INCLUDED
