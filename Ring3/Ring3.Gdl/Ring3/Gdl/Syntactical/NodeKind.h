/// @file Ring3/Gdl/Syntactical/NodeKind.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED)
#define RING3_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Syntactical/NodeKind.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"
#include "Ring3/Gdl/Configuration.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_Gdl_NodeKind)

enum Machine_Gdl_NodeKind {
#define Define(SymbolicConstant, Variable, String) \
  SymbolicConstant,
#include "Ring3/Gdl/Syntactical/NodeKind.i"
#undef Define
};

Ring1_NoDiscardReturn() Ring2_String*
Machine_Gdl_NodeKind_toString
  (
    Machine_Gdl_NodeKind self
  );

#endif // RING3_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED
