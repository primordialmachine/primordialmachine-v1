/// @file Signals/Connection.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_SIGNALS_SIGNAL_H_INCLUDED)
#define MACHINE_SIGNALS_SIGNAL_H_INCLUDED



#if !defined(MACHINE_SIGNALS_PRIVATE)
#error("Do not include this file directly, include `_Signals.h` instead.")
#endif

#include "_Collections.h"



/// C-level representation of a signal.
/// List of connections.
/// Subscribe (add connection) and unsubscribe (remove connection).
/// /// The HLL-level definition is
/// @code
/// class Machine.Signals.Signal {
///   ...
///   construct()
/// 
///   void emit(String name, ...)
///   ...
/// }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Machine_Signals_Signal)

struct Machine_Signals_Signal_Class {
  Machine_Object_Class parent__;
};

struct Machine_Signals_Signal {
  Machine_Object parent__;
  Machine_List* connections;
};

void Machine_Signals_Signal_construct(Machine_Signals_Signal* self, size_t numberOfArguments, Machine_Value const* arguments);

Machine_Signals_Signal* Machine_Signals_Signal_create();

void Machine_Signals_Signal_subscribe(Machine_Signals_Signal *self, Ring2_String* name, Machine_Object* context, Machine_ForeignProcedure *callback);

void Machine_Signals_Signal_unsubscribe(Machine_Signals_Signal *self, Ring2_String* name, Machine_Object* context, Machine_ForeignProcedure* callback);

void Machine_Signals_Signal_emit(Machine_Signals_Signal* self, Ring2_String* name, size_t numberOfArguments, Machine_Value const* arguments);



#endif // MACHINE_SIGNALS_SIGNAL_H_INCLUDED
