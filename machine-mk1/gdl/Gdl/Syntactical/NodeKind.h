/// @file Gdl/Syntactical/NodeKind.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED)
#define MACHINE_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED

#include "Ring2/Library/_Include.h"

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

#endif // MACHINE_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED
