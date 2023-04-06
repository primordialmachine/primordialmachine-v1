/// @file Ring3/Gdl/Lexical/TokenKind.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED)
#define RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/TokenKind.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Configuration.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_Gdl_TokenKind)

enum Ring3_Gdl_TokenKind {

#define Define(SymbolicConstant, Variable, String) \
  SymbolicConstant,
#include "Ring3/Gdl/Lexical/TokenKind.i"
#undef Define
};

Ring1_CheckReturn() Ring2_String*
Ring3_Gdl_TokeneKind_toString
  (
    Ring3_Gdl_TokenKind self
  );

#endif // RING3_GDL_LEXICAL_TOKENKIND_H_INCLUDED
