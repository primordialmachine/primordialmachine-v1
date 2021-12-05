/// @file GDL/Extensions.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GDL/Extensions.h"

#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

static Machine_Value convert(Machine_GDL_Node* self, Machine_GDL_Context* context) {
  switch (self->kind) {
  case Machine_GDL_NodeKind_Boolean: {
    Machine_Boolean temporary = Machine_GDL_Node_toBoolean(self, context);
    Machine_Value value;
    Machine_Value_setBoolean(&value, temporary);
    return value;
  }
  case Machine_GDL_NodeKind_Integer: {
    Machine_Integer temporary = Machine_GDL_Node_toInteger(self, context);
    Machine_Value value;
    Machine_Value_setInteger(&value, temporary);
    return value;
  }
  case Machine_GDL_NodeKind_Key: {
    Machine_String* temporary = Machine_GDL_Node_toString(self, context);
    Machine_Value value;
    Machine_Value_setString(&value, temporary);
    return value;
  }
  case Machine_GDL_NodeKind_Pair: {
    Machine_Pair *temporary = Machine_GDL_Node_toPair(self, context);
    Machine_Value value;
    Machine_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_GDL_NodeKind_Real: {
    Machine_Real temporary = Machine_GDL_Node_toReal(self, context);
    Machine_Value value;
    Machine_Value_setReal(&value, temporary);
    return value;
  }
  case Machine_GDL_NodeKind_String: {
    Machine_String* temporary = Machine_GDL_Node_toString(self, context);
    Machine_Value value;
    Machine_Value_setString(&value, temporary);
    return value;
  }
  case Machine_GDL_NodeKind_List: {
    Machine_List* temporary = Machine_GDL_Node_toList(self, context);
    Machine_Value value;
    Machine_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_GDL_NodeKind_Map: {
    Machine_Map* temporary = Machine_GDL_Node_toMap(self, context);
    Machine_Value value;
    Machine_Value_setObject(&value, (Machine_Object *)temporary);
    return value;
  }
  case Machine_GDL_NodeKind_Void: {
    Machine_Void temporary = Machine_GDL_Node_toVoid(self, context);
    Machine_Value value;
    Machine_Value_setVoid(&value, temporary);
    return value;
  }
  default:
    MACHINE_ASSERT_UNREACHABLE();
  };
}

Machine_Boolean Machine_GDL_Node_toBoolean(Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Boolean, Machine_Status_InvalidArgument);
  if (Machine_String_isEqualTo(self->text, context->trueLiteral)) {
    return true;
  } else {
    return false;
  }
}

Machine_Integer Machine_GDL_Node_toInteger(Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Integer || self->kind == Machine_GDL_NodeKind_Real, Machine_Status_InvalidArgument);
  char buffer[1024 + 1];
  size_t n =  Machine_String_getNumberOfBytes(self->text);
  if (n > 1024) {
    Machine_setStatus(Machine_Status_InvalidOperation); // TODO: Should be "ConversionFailed".
    Machine_jump();
  }
  Machine_Eal_copy(buffer, Machine_String_getBytes(self->text), n, false);
  buffer[n] = '\0';
  Machine_Integer v;
  if (sscanf(buffer, "%"SCNd64, &v) != 1) {
    Machine_setStatus(Machine_Status_InvalidOperation); // TODO: Should be "ConversionFailed".
    Machine_jump();
  }
  return v;
}

Machine_List* Machine_GDL_Node_toList(const Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_List, Machine_Status_InvalidArgument);
  Machine_List* targets = Machine_List_create();
  for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)self->children); i < n; ++i) {
    Machine_Value v = Machine_List_getAt(self->children, i);
    Machine_GDL_Node* source = (Machine_GDL_Node*)Machine_Value_getObject(&v);
    v = convert(source, context);
    Machine_List_append(targets, v);
  }
  return targets;
}

Machine_Map* Machine_GDL_Node_toMap(const Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Map, Machine_Status_InvalidArgument);
  Machine_Map* targets = Machine_Map_create();
  for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)self->children); i < n; ++i) {
    Machine_Value v = Machine_List_getAt(self->children, i);
    Machine_GDL_Node* sourcePair = (Machine_GDL_Node*)Machine_Value_getObject(&v);
    Machine_Pair* targetPair = Machine_GDL_Node_toPair(sourcePair, context);
    Machine_Map_set(targets, Machine_Pair_get(targetPair, 0), Machine_Pair_get(targetPair, 1));
  }
  return targets;
}

Machine_Pair* Machine_GDL_Node_toPair(const Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Pair, Machine_Status_InvalidArgument);
  Machine_Value x = Machine_List_getAt(self->children, 0),
    y = Machine_List_getAt(self->children, 1);
  Machine_GDL_Node* a = (Machine_GDL_Node*)Machine_Value_getObject(&x),
    * b = (Machine_GDL_Node*)Machine_Value_getObject(&y);
  return Machine_Pair_create(convert(a, context), convert(b, context));
}

Machine_Real Machine_GDL_Node_toReal(Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Integer || self->kind == Machine_GDL_NodeKind_Real, Machine_Status_InvalidArgument);
  char buffer[1024 + 1];
  size_t n = Machine_String_getNumberOfBytes(self->text);
  if (n > 1024) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  Machine_Eal_copy(buffer, Machine_String_getBytes(self->text), n, false);
  buffer[n] = '\0';
  Machine_Real v;
  if (sscanf(buffer, "%f", &v) != 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return v;
}

Machine_String* Machine_GDL_Node_toString(const Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Key || self->kind == Machine_GDL_NodeKind_String, Machine_Status_InvalidArgument);
  return self->text;
}

Machine_Void Machine_GDL_Node_toVoid(const Machine_GDL_Node* self, Machine_GDL_Context* context) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT(self->kind == Machine_GDL_NodeKind_Void, Machine_Status_InvalidArgument);
  return Machine_Void_Void;
}
