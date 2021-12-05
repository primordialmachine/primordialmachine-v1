/// @file Gdl/Extensions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_EXTENSIONS_H_INCLUDED)
#define MACHINE_GDL_EXTENSIONS_H_INCLUDED


#include "./../GDL/Syntactical/Node.h"


/// @brief Convert a node to a value of type <code>Boolean</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Boolean.
/// @return The value of type <code>Boolean</code>.
/// @extension 
Machine_Boolean Machine_GDL_Node_toBoolean(Machine_GDL_Node* self, Machine_GDL_Context* context);

/// @brief Convert a number node to a value of type <code>Integer</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Integer or Machine_GDL_NodeKind_Real.
/// @return The value of type <code>Integer</code>.
/// @extension 
Machine_Integer Machine_GDL_Node_toInteger(Machine_GDL_Node* self, Machine_GDL_Context* context);

/// @brief Convert a node to a value of type <code>List</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_List.
/// @return The value of type <code>List</code>.
/// @extension
/// @remark List elements are subjected to default conversion rules.
/// - GDL boolean is mapped to <code>Boolean</code> as defined by Machine_GDL_Node_toBoolean(const Machine_GDL_Node *).
/// - GDL integer is mapped to <code>Integer</code> as defined by Machine_GDL_Node_toInteger(const Machine_GDL_Node *).
/// - GDL list is mapped to <code>List</code> as defined by Machine_GDL_Node_toList(const Machine_GDL_Node *).
/// - GDL map is mapped to <code>Map</code> as defined by Machine_GDL_Node_toMap(const Machine_GDL_Node *).
/// - GDL key is mapped to <code>String</code> as defined by Machine_GDL_Node_toString(const Machine_GDL_Node *).
/// - GDL pair is mapped to <code>Pair</code> as defined by Machine_GDL_Node_toPair(const Machine_GDL_Node *).
/// - GDL real is mapped to <code>Real</code> as defined by Machine_GDL_Node_toReal(const Machine_GDL_Node *).
/// - GDL string is mapped to <code>String</code> as defined by Machine_GDL_Node_toString(const Machine_GDL_Node *).
/// - GDL void is mapped to <code>Void</code> as defined by Machine_GDL_Node_toVoid(const Machine_GDL_Node *).
Machine_List* Machine_GDL_Node_toList(const Machine_GDL_Node* self, Machine_GDL_Context* context);

/// @brief Convert a node to a value of type <code>Map</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Map.
/// @return The value of type <code>Map</code>.
/// @extension
/// @remark Pair elements are subjected to the conversions as described in Machine_GDL_Node_toList.
Machine_Map* Machine_GDL_Node_toMap(const Machine_GDL_Node* self, Machine_GDL_Context* context);

/// @brief Convert a node to a value of type <code>Pair</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Pair.
/// @return The value of type <code>Pair</code>.
/// @extension
/// @remark Pair elements are subjected to the conversions as described in Machine_GDL_Node_toList.
Machine_Pair* Machine_GDL_Node_toPair(const Machine_GDL_Node* self, Machine_GDL_Context* context);

/// @brief Convert a node to a value of type <code>Real</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Integer or Machine_GDL_NodeKind_Real.
/// @return The value of type <code>Real</code>.
/// @extension 
Machine_Real Machine_GDL_Node_toReal(Machine_GDL_Node *self, Machine_GDL_Context* context);

/// @brief Convert a node to a value of type <code>String</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Key and Machine_GDL_NodeKind_String.
/// @return The value of type <code>String</code>.
/// @extension
Machine_String* Machine_GDL_Node_toString(const Machine_GDL_Node *self, Machine_GDL_Context* context);

/// @brief Convert a void node to a value of type <code>Void</code>.
/// @param self This node. Must be of kind Machine_GDL_NodeKind_Void.
/// @return The value of type <code>Void</code>.
/// @extension 
Machine_Void Machine_GDL_Node_toVoid(const Machine_GDL_Node* self, Machine_GDL_Context* context);


#endif // MACHINE_GDL_EXTENSIONS_H_INCLUDED
