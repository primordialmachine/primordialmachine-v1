/// @file Ring3/Signals/Connection.h
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_SIGNALS_SIGNAL_H_INCLUDED)
#define RING3_SIGNALS_SIGNAL_H_INCLUDED

#if !defined(RING3_SIGNALS_PRIVATE)
#error("Do not include `Ring3/Signals/Singla.h` directly, include `Ring3/Signals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// C-level representation of a signal.
/// List of connections.
/// Subscribe (add connection) and unsubscribe (remove connection).
/// /// The HLL-level definition is
/// @code
/// class Ring3.Signals.Signal {
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
  Ring2_Collections_List* connections;
};

void Machine_Signals_Signal_construct(Machine_Signals_Signal* self, size_t numberOfArguments, Ring2_Value const* arguments);

Machine_Signals_Signal* Machine_Signals_Signal_create();

void Machine_Signals_Signal_subscribe(Machine_Signals_Signal *self, Ring2_String* name, Machine_Object* context, Ring2_ForeignProcedure *callback);

void Machine_Signals_Signal_unsubscribe(Machine_Signals_Signal *self, Ring2_String* name, Machine_Object* context, Ring2_ForeignProcedure* callback);

void Machine_Signals_Signal_emit(Machine_Signals_Signal* self, Ring2_String* name, size_t numberOfArguments, Ring2_Value const* arguments);



#endif // RING3_SIGNALS_SIGNAL_H_INCLUDED
