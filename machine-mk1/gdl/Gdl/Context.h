/// @file Gdl/Context.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_CONTEXT_H_INCLUDED)
#define MACHINE_GDL_CONTEXT_H_INCLUDED

#include "Gdl/Syntactical/NodeKind.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Context)

struct Machine_Gdl_Context_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Context {
  Machine_Object __parent;
  Machine_String* trueLiteral;
  Machine_String* falseLiteral;
  Machine_String* voidLiteral;
};

Machine_Gdl_Context* Machine_Gdl_Context_create();

#endif // MACHINE_GDL_CONTEXT_H_INCLUDED
