/// @file Ring3/Gdl/Context.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_CONTEXT_H_INCLUDED)
#define RING3_GDL_CONTEXT_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Context.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Context)

struct Machine_Gdl_Context_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Context {
  Machine_Object __parent;
  Ring2_String* trueLiteral;
  Ring2_String* falseLiteral;
  Ring2_String* voidLiteral;
};

/// @brief Create a GDL context.
/// @return A pointer to the GDL context.
Machine_Gdl_Context*
Machine_Gdl_Context_create
  (
  );

#endif // RING3_GDL_CONTEXT_H_INCLUDED
