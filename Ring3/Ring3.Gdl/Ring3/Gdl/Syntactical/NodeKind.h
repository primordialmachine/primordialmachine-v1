/// @file Ring3/Gdl/Syntactical/NodeKind.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED)
#define RING3_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Syntactical/NodeKind.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_Gdl_NodeKind)

enum Machine_Gdl_NodeKind {

  /// @brief "compilation unit".
  Machine_Gdl_NodeKind_CompilationUnit,

  /// @brief "map := pair*".
  Machine_Gdl_NodeKind_Map,

  /// @brief "list := value*".
  Machine_Gdl_NodeKind_List,

  /// @brief "key := NAME".
  Machine_Gdl_NodeKind_Key,

  /// @brief "pair := key value".
  Machine_Gdl_NodeKind_Pair,

  /// @brief "boolean := BOOLEAN".
  Machine_Gdl_NodeKind_Boolean,

  /// @brief "integer := INTEGER".
  Machine_Gdl_NodeKind_Integer,

  /// @brief "real := REAL".
  Machine_Gdl_NodeKind_Real,

  /// @brief "string := STRING".
  Machine_Gdl_NodeKind_String,

  /// @brief "void := VOID".
  Machine_Gdl_NodeKind_Void,

};

#endif // RING3_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED
