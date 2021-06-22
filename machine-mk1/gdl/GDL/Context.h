/// @file GDL/Context.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_CONTEXT_H_INCLUDED)
#define MACHINE_GDL_CONTEXT_H_INCLUDED


#include "./../GDL/Syntactical/NodeKind.h"


MACHINE_DECLARE_CLASSTYPE(Machine_GDL_Context)

struct Machine_GDL_Context {
  Machine_Object __parent;
  Machine_String* trueLiteral;
  Machine_String* falseLiteral;
  Machine_String* voidLiteral;
};

Machine_GDL_Context* Machine_GDL_Context_create();


#endif // MACHINE_GDL_CONTEXT_H_INCLUDED
