/// @file Gdl/Extensions.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gdl/Extensions.h"

#include "Ring1/Status.h"
#include "Ring1/Conversion.h"

static Machine_Value convert(Machine_Gdl_Node* self, Machine_Gdl_Context* context) {
  switch (self->kind) {
  case Machine_Gdl_NodeKind_Boolean: {
    Ring2_Boolean temporary = Machine_Gdl_Node_toBoolean(self, context);
    Machine_Value value;
    Machine_Value_setBoolean(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Integer: {
    Ring2_Integer temporary = Machine_Gdl_Node_toInteger(self, context);
    Machine_Value value;
    Machine_Value_setInteger(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Key: {
    Ring2_String* temporary = Machine_Gdl_Node_toString(self, context);
    Machine_Value value;
    Machine_Value_setString(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Pair: {
    Machine_Pair *temporary = Machine_Gdl_Node_toPair(self, context);
    Machine_Value value;
    Machine_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Real: {
    Ring2_Real32 temporary = Machine_Gdl_Node_toReal(self, context);
    Machine_Value value;
    Machine_Value_setReal32(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_String: {
    Ring2_String* temporary = Machine_Gdl_Node_toString(self, context);
    Machine_Value value;
    Machine_Value_setString(&value, temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_List: {
    Machine_List* temporary = Machine_Gdl_Node_toList(self, context);
    Machine_Value value;
    Machine_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Map: {
    Machine_Map* temporary = Machine_Gdl_Node_toMap(self, context);
    Machine_Value value;
    Machine_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_Gdl_NodeKind_Void: {
    Ring2_Void temporary = Machine_Gdl_Node_toVoid(self, context);
    Machine_Value value;
    Machine_Value_setVoid(&value, temporary);
    return value;
  }
  default:
    MACHINE_ASSERT_UNREACHABLE();
  };
}

Ring2_Boolean Machine_Gdl_Node_toBoolean(Machine_Gdl_Node* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Boolean, Ring1_Status_InvalidArgument);
  bool value;
  if (Ring1_Conversion_stringToBool(&value, Ring2_String_getBytes(Ring2_Context_get(), self->text),
                                    Ring2_String_getBytes(Ring2_Context_get(), self->text) +
                                    Ring2_String_getNumberOfBytes(Ring2_Context_get(), self->text))) {
    Ring2_jump();
  }
  return value;
}

Ring2_Integer Machine_Gdl_Node_toInteger(Machine_Gdl_Node* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Integer || self->kind == Machine_Gdl_NodeKind_Real, Ring1_Status_InvalidArgument);
  int64_t value;
  if (Ring1_Conversion_stringToInt64(&value, 
                                     Ring2_String_getBytes(Ring2_Context_get(), self->text),
                                     Ring2_String_getBytes(Ring2_Context_get(), self->text) +
                                     Ring2_String_getNumberOfBytes(Ring2_Context_get(), self->text))) {
    Ring2_jump();
  }
  return value;
}

Machine_List* Machine_Gdl_Node_toList(Machine_Gdl_Node const* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_List, Ring1_Status_InvalidArgument);
  Machine_List* targets = (Machine_List *)Machine_ArrayList_create();
  for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)self->children); i < n; ++i) {
    Machine_Value v = Machine_List_getAt(self->children, i);
    Machine_Gdl_Node* source = (Machine_Gdl_Node*)Machine_Value_getObject(&v);
    v = convert(source, context);
    Machine_List_append(targets, v);
  }
  return targets;
}

Machine_Map* Machine_Gdl_Node_toMap(Machine_Gdl_Node const* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Map, Ring1_Status_InvalidArgument);
  Machine_Map* targets = (Machine_Map *)Machine_HashMap_create();
  for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection *)self->children); i < n; ++i) {
    Machine_Value v = Machine_List_getAt(self->children, i);
    Machine_Gdl_Node* sourcePair = (Machine_Gdl_Node*)Machine_Value_getObject(&v);
    Machine_Pair* targetPair = Machine_Gdl_Node_toPair(sourcePair, context);
    Machine_Map_set(targets, Machine_Pair_get(targetPair, 0), Machine_Pair_get(targetPair, 1));
  }
  return targets;
}

Machine_Pair* Machine_Gdl_Node_toPair(Machine_Gdl_Node const* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Pair, Ring1_Status_InvalidArgument);
  Machine_Value x = Machine_List_getAt(self->children, 0),
                y = Machine_List_getAt(self->children, 1);
  Machine_Gdl_Node* a = (Machine_Gdl_Node*)Machine_Value_getObject(&x),
                  * b = (Machine_Gdl_Node*)Machine_Value_getObject(&y);
  return Machine_Pair_create(convert(a, context), convert(b, context));
}

Ring2_Real32 Machine_Gdl_Node_toReal(Machine_Gdl_Node* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Integer || self->kind == Machine_Gdl_NodeKind_Real, Ring1_Status_InvalidArgument);
  double value;
  if (Ring1_Conversion_stringToDouble(&value, 
                                      Ring2_String_getBytes(Ring2_Context_get(), self->text),
                                      Ring2_String_getBytes(Ring2_Context_get(), self->text) +
                                      Ring2_String_getNumberOfBytes(Ring2_Context_get(), self->text))) {
    Ring2_jump();
  }
  return value;
}

Ring2_String* Machine_Gdl_Node_toString(Machine_Gdl_Node const* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Key || self->kind == Machine_Gdl_NodeKind_String, Ring1_Status_InvalidArgument);
  return self->text;
}

Ring2_Void Machine_Gdl_Node_toVoid(Machine_Gdl_Node const* self, Machine_Gdl_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_Gdl_NodeKind_Void, Ring1_Status_InvalidArgument);
  return Ring2_Void_Void;
}
