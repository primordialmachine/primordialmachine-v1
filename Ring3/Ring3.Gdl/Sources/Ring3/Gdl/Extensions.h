/// @file Ring3/Gdl/Extensions.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_EXTENSIONS_H_INCLUDED)
#define RING3_GDL_EXTENSIONS_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Extensions.h` directly. Include `Ring3/Gdl/_Include.h` instead.")#endif
#endif
#include "Ring3/Gdl/header.h.i"

/// @brief Convert a node to a value of type <code>Boolean</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Boolean.
/// @return The value of type <code>Boolean</code>.
/// @extension
Ring1_NoDiscardReturn() Ring2_Boolean
Machine_Gdl_Node_toBoolean
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a number node to a value of type <code>Integer</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Integer or
/// Machine_Gdl_NodeKind_Real.
/// @return The value of type <code>Integer</code>.
/// @extension
Ring1_NoDiscardReturn() Ring2_Integer
Machine_Gdl_Node_toInteger
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a node to a value of type <code>List</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_List.
/// @return The value of type <code>List</code>.
/// @extension
/// @remark List elements are subjected to default conversion rules.
/// - GDL boolean is mapped to <code>Boolean</code> as defined by
/// Machine_Gdl_Node_toBoolean(Machine_Gdl_Node const*).
/// - GDL integer is mapped to <code>Integer</code> as defined by
/// Machine_Gdl_Node_toInteger(Machine_Gdl_Node const*).
/// - GDL list is mapped to <code>List</code> as defined by
/// Machine_Gdl_Node_toList(Machine_Gdl_Node const*).
/// - GDL map is mapped to <code>Map</code> as defined by
/// Machine_Gdl_Node_toMap(Machine_Gdl_Node const*).
/// - GDL key is mapped to <code>String</code> as defined by
/// Machine_Gdl_Node_toString(Machine_Gdl_Node const*).
/// - GDL pair is mapped to <code>Pair</code> as defined by
/// Machine_Gdl_Node_toPair(Machine_Gdl_Node const *).
/// - GDL real is mapped to <code>Real</code> as defined by
/// Machine_Gdl_Node_toReal(Machine_Gdl_Node const *).
/// - GDL string is mapped to <code>String</code> as defined by
/// Machine_Gdl_Node_toString(Machine_Gdl_Node const *).
/// - GDL void is mapped to <code>Void</code> as defined by
/// Machine_Gdl_Node_toVoid(Machine_Gdl_Node const*).
Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gdl_Node_toList
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a node to a value of type <code>Map</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Map.
/// @return The value of type <code>Map</code>.
/// @extension
/// @remark Pair elements are subjected to the conversions as described in Machine_Gdl_Node_toList.
Ring1_NoDiscardReturn() Ring2_Collections_Map*
Machine_Gdl_Node_toMap
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a node to a value of type <code>Pair</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Pair.
/// @return The value of type <code>Pair</code>.
/// @extension
/// @remark Pair elements are subjected to the conversions as described in Machine_Gdl_Node_toList.
Ring1_NoDiscardReturn() Ring2_Collections_Pair*
Machine_Gdl_Node_toPair
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a node to a value of type <code>Real</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Integer or
/// Machine_Gdl_NodeKind_Real.
/// @return The value of type <code>Real</code>.
/// @extension
Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gdl_Node_toReal
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a node to a value of type <code>String</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Key and Machine_Gdl_NodeKind_String.
/// @return The value of type <code>String</code>.
/// @extension
Ring1_NoDiscardReturn() Ring2_String*
Machine_Gdl_Node_toString
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  );

/// @brief Convert a void node to a value of type <code>Void</code>.
/// @param self This node. Must be of kind Machine_Gdl_NodeKind_Void.
/// @return The value of type <code>Void</code>.
/// @extension
Ring1_NoDiscardReturn() Ring2_Void
Machine_Gdl_Node_toVoid
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  );

#endif // RING3_GDL_EXTENSIONS_H_INCLUDED
