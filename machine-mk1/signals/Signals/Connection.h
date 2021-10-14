/// @file Signals/Connection.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_SIGNALS_CONNECTION_H_INCLUDED)
#define MACHINE_SIGNALS_CONNECTION_H_INCLUDED

#if !defined(MACHINE_SIGNALS_PRIVATE)
#error("Do not include this file directly, include `_Signals.h` instead.")
#endif

#include "_Runtime.h"

/// C-level definition of a connection.
/// The HLL-level definition is
/// @code
/// class Machine.Signals.Connection { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Machine_Signals_Connection)

struct Machine_Signals_Connection_Class {
  Machine_Object_Class parent;
};

struct Machine_Signals_Connection {
  Machine_Object parent;
  Machine_String* name;
  Machine_Object* context;
  Machine_ForeignProcedure* callback;
};

void Machine_Signals_Connection_construct(Machine_Signals_Connection* self, size_t numberOfArguments, const Machine_Value* arguments);

Machine_Signals_Connection* Machine_Signals_Connection_create(Machine_String *name, Machine_Object* context, Machine_ForeignProcedure* callback);

#endif // MACHINE_SIGNALS_CONNECTION_H_INCLUDED
