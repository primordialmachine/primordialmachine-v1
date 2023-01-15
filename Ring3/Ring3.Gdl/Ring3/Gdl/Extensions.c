/// @file Ring3/Gdl/Extensions.c
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Extensions.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/Conversion.h"
#include "Ring1/All/_Include.h"
#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Syntactical/Node.h"
#undef RING3_GDL_PRIVATE


Ring1_NoDiscardReturn() static Ring2_Value
convert
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  )
{
  switch (self->kind) {
  case Machine_Gdl_NodeKind_Boolean: {
    Ring2_Boolean temporary = Machine_Gdl_Node_toBoolean(self, context);
    Ring2_Value value;
    Ring2_Value_setBoolean(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Integer: {
    Ring2_Integer temporary = Machine_Gdl_Node_toInteger(self, context);
    Ring2_Value value;
    Ring2_Value_setInteger(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Name: {
    Ring2_String* temporary = Machine_Gdl_Node_toString(self, context);
    Ring2_Value value;
    Ring2_Value_setString(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Pair: {
    Ring2_Collections_Pair *temporary = Machine_Gdl_Node_toPair(self, context);
    Ring2_Value value;
    Ring2_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Real: {
    Ring2_Real32 temporary = Machine_Gdl_Node_toReal(self, context);
    Ring2_Value value;
    Ring2_Value_setReal32(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_String: {
    // We want the canonical form of a string.
    Ring3_Gdl_StringLiteral *stringLiteral = (Ring3_Gdl_StringLiteral*)Ring2_Value_getObject(&self->value);
    Ring2_String* temporary = Ring3_Gdl_StringLiteral_toString(stringLiteral, true);
    Ring2_Value value;
    Ring2_Value_setString(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_List: {
    Ring2_Collections_List* temporary = Machine_Gdl_Node_toList(self, context);
    Ring2_Value value;
    Ring2_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Map: {
    Ring2_Collections_Map* temporary = Machine_Gdl_Node_toMap(self, context);
    Ring2_Value value;
    Ring2_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Void: {
    Ring2_Void temporary = Machine_Gdl_Node_toVoid(self, context);
    Ring2_Value value;
    Ring2_Value_setVoid(&value, temporary);
    return value;
  }
  default:
    Ring2_unreachable();
  };
}

Ring1_NoDiscardReturn() Ring2_Boolean
Machine_Gdl_Node_toBoolean
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Boolean, Ring1_Status_InvalidArgument);
  return Ring3_Gdl_BooleanLiteral_toBoolean((Ring3_Gdl_BooleanLiteral*)Ring2_Value_getObject(&self->value));
}

Ring1_NoDiscardReturn() Ring2_Integer
Machine_Gdl_Node_toInteger
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Integer || self->kind == Machine_Gdl_NodeKind_Real, Ring1_Status_InvalidArgument);
  if (Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(Ring2_Value_getObject(&self->value)), (Machine_Type*)Ring3_Gdl_IntegerLiteral_getType())) {
    return Ring3_Gdl_IntegerLiteral_toInteger((Ring3_Gdl_IntegerLiteral*)Ring2_Value_getObject(&self->value));
  } else if (Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(Ring2_Value_getObject(&self->value)), (Machine_Type*)Ring3_Gdl_RealLiteral_getType())) {
    return Ring3_Gdl_RealLiteral_toInteger((Ring3_Gdl_RealLiteral*)Ring2_Value_getObject(&self->value));
  } else {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

Ring1_NoDiscardReturn() Ring2_Collections_List*
Machine_Gdl_Node_toList
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_List, Ring1_Status_InvalidArgument);
  Ring2_Collections_List* targets = (Ring2_Collections_List *)Ring2_Collections_ArrayList_create();
  for (size_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->children); i < n; ++i) {
    Ring2_Value v = Ring2_Collections_List_getAt(self->children, i);
    Machine_Gdl_Node* source = (Machine_Gdl_Node*)Ring2_Value_getObject(&v);
    v = convert(source, context);
    Ring2_Collections_List_append(targets, v);
  }
  return targets;
}

Ring1_NoDiscardReturn() Ring2_Collections_Map*
Machine_Gdl_Node_toMap
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Map, Ring1_Status_InvalidArgument);
  Ring2_Collections_Map* targets = (Ring2_Collections_Map *)Ring2_Collections_HashMap_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, self->children)); i < n; ++i) {
    Ring2_Value v = Ring2_Collections_List_getAt(self->children, i);
    Machine_Gdl_Node* sourcePair = (Machine_Gdl_Node*)Ring2_Value_getObject(&v);
    Ring2_Collections_Pair* targetPair = Machine_Gdl_Node_toPair(sourcePair, context);
    Ring2_Collections_Map_set(targets, Ring2_Collections_Pair_get(targetPair, 0), Ring2_Collections_Pair_get(targetPair, 1));
  }
  return targets;
}

Ring1_NoDiscardReturn() Ring2_Collections_Pair*
Machine_Gdl_Node_toPair
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Pair, Ring1_Status_InvalidArgument);
  Ring2_Value x = Ring2_Collections_List_getAt(self->children, 0),
              y = Ring2_Collections_List_getAt(self->children, 1);
  Machine_Gdl_Node* a = (Machine_Gdl_Node*)Ring2_Value_getObject(&x),
                  * b = (Machine_Gdl_Node*)Ring2_Value_getObject(&y);
  return Ring2_Collections_Pair_create(convert(a, context), convert(b, context));
}

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gdl_Node_toReal
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Integer || self->kind == Machine_Gdl_NodeKind_Real, Ring1_Status_InvalidArgument);
  if (Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(Ring2_Value_getObject(&self->value)), (Machine_Type*)Ring3_Gdl_IntegerLiteral_getType())) {
    return Ring3_Gdl_IntegerLiteral_toReal32((Ring3_Gdl_IntegerLiteral*)Ring2_Value_getObject(&self->value));
  } else if (Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(Ring2_Value_getObject(&self->value)), (Machine_Type*)Ring3_Gdl_RealLiteral_getType())) {
    return Ring3_Gdl_RealLiteral_toReal32((Ring3_Gdl_RealLiteral*)Ring2_Value_getObject(&self->value));
  } else {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

Ring1_NoDiscardReturn() Ring2_String*
Machine_Gdl_Node_toString
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Name || self->kind == Machine_Gdl_NodeKind_String, Ring1_Status_InvalidArgument);
  if (Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(Ring2_Value_getObject(&self->value)), (Machine_Type*)Ring3_Gdl_Name_getType())) {
    return Ring3_Gdl_Name_toString((Ring3_Gdl_Name*)Ring2_Value_getObject(&self->value));
  } else if (Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(Ring2_Value_getObject(&self->value)), (Machine_Type*)Ring3_Gdl_StringLiteral_getType())) {
    return Ring3_Gdl_StringLiteral_toString((Ring3_Gdl_StringLiteral*)Ring2_Value_getObject(&self->value), true);
  } else {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
}

Ring1_NoDiscardReturn() Ring2_Void
Machine_Gdl_Node_toVoid
  (
    Machine_Gdl_Node const* self,
    Machine_Gdl_Context* context
  )
{
  Ring2_assertNotNull(self);
  Ring2_assert(self->kind == Machine_Gdl_NodeKind_Void, Ring1_Status_InvalidArgument);
  return Ring2_Void_Void;
}
