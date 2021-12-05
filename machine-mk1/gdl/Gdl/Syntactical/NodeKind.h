/// @file Gdl/Syntactical/NodeKind.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED)
#define MACHINE_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED


#include "_Runtime.h"


typedef enum Machine_GDL_NodeKind Machine_GDL_NodeKind;

enum Machine_GDL_NodeKind {

  /// @brief "compilation unit".
  Machine_GDL_NodeKind_CompilationUnit,

  /// @brief "map := pair*".
  Machine_GDL_NodeKind_Map,

  /// @brief "list := value*".
  Machine_GDL_NodeKind_List,

  /// @brief "key := NAME".
  Machine_GDL_NodeKind_Key,

  /// @brief "pair := key value".
  Machine_GDL_NodeKind_Pair,

  /// @brief "boolean := BOOLEAN".
  Machine_GDL_NodeKind_Boolean,

  /// @brief "integer := INTEGER".
  Machine_GDL_NodeKind_Integer,

  /// @brief "real := REAL".
  Machine_GDL_NodeKind_Real,

  /// @brief "string := STRING".
  Machine_GDL_NodeKind_String,

  /// @brief "void := VOID".
  Machine_GDL_NodeKind_Void,

};


#endif // MACHINE_GDL_SYNTACTICAL_NODEKIND_H_INCLUDED
