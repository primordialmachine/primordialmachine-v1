/// @file Gdl/Lexical/TokenKind.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED)
#define RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/TokenKind.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_Gdl_TokenKind)

enum Machine_Gdl_TokenKind {

#define Define(SymbolicConstant, Variable, String) \
  SymbolicConstant,
#include "Ring3/Gdl/Lexical/TokenKind.i"
#undef Define
};

Ring1_CheckReturn() Ring2_String*
Machine_Gdl_TokeneKind_toString
  (
    Machine_Gdl_TokenKind self
  );

#endif // RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED
