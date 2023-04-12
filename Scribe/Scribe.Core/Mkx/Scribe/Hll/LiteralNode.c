// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/LiteralNode.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Hll/LiteralNode.h"


#include "Ring2/Operations.h"


static void
Mkx_Scribe_Hll_LiteralNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Hll_LiteralNode* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Hll_LiteralNode, Mkx_Scribe_Hll_Node, &Mkx_Scribe_Hll_LiteralNode_visit, 
                         &Mkx_Scribe_Hll_LiteralNode_construct, NULL, NULL, NULL)

static void
Mkx_Scribe_Hll_LiteralNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Hll_LiteralNode* self
  )
{
  Ring2_Value_visit(gc, &self->value);
}

void
Mkx_Scribe_Hll_LiteralNode_construct
  (
    Mkx_Scribe_Hll_LiteralNode* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  // Only the first two are passed.
  Mkx_Scribe_Hll_Node_construct((Mkx_Scribe_Hll_Node*)self, 2, arguments);
  self->value = arguments[2];
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Hll_LiteralNode_getType());
}

Mkx_Scribe_Hll_LiteralNode*
Mkx_Scribe_Hll_LiteralNode_createFromIntegerLiteralString
  (
    Mkx_Scribe_Position* position,
    Ring2_String* literalString
  )
{
  Machine_Type* ty = Mkx_Scribe_Hll_LiteralNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], Mkx_Scribe_Hll_NodeType_Integer);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,position));
  Ring2_Value_setString(&arguments[2], literalString);
  Mkx_Scribe_Hll_LiteralNode *self = Ring1_cast(Mkx_Scribe_Hll_LiteralNode*,
                                                Machine_allocateClassObject(ty,
                                                                            NUMBER_OF_ARGUMENTS,
                                                                            arguments));
  return self;
}

Mkx_Scribe_Hll_LiteralNode*
Mkx_Scribe_Hll_LiteralNode_createFromStringLiteralString
  (
    Mkx_Scribe_Position* position,
    Ring2_String* literalString
  )
{
  Machine_Type* ty = Mkx_Scribe_Hll_LiteralNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], Mkx_Scribe_Hll_NodeType_String);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,position));
  Ring2_Value_setString(&arguments[2], literalString);
  Mkx_Scribe_Hll_LiteralNode *self = Ring1_cast(Mkx_Scribe_Hll_LiteralNode*,
                                                Machine_allocateClassObject(ty,
                                                                            NUMBER_OF_ARGUMENTS,
                                                                            arguments));
  return self;
}

Mkx_Scribe_Hll_LiteralNode*
Mkx_Scribe_Hll_LiteralNode_createFromNameLiteralString
  (
    Mkx_Scribe_Position* position,
    Ring2_String* literalString
  )
{
  Machine_Type* ty = Mkx_Scribe_Hll_LiteralNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], Mkx_Scribe_Hll_NodeType_Name);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,position));
  Ring2_Value_setString(&arguments[2], literalString);
  Mkx_Scribe_Hll_LiteralNode *self = Ring1_cast(Mkx_Scribe_Hll_LiteralNode*,
                                                Machine_allocateClassObject(ty,
                                                                            NUMBER_OF_ARGUMENTS,
                                                                            arguments));
  return self;
}

Ring2_Integer
Mkx_Scribe_Hll_LiteralNode_getInteger
  (
    Mkx_Scribe_Hll_LiteralNode* self
  )
{
  if (Mkx_Scribe_Hll_Node_getKind(Ring1_cast(Mkx_Scribe_Hll_Node*, self)) != Mkx_Scribe_Hll_NodeType_Integer)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Ring2_String* stringLiteral = Ring2_Value_getString(&self->value);
  return Ring2_Integer_fromString(Ring2_Context_get(), stringLiteral);
}

Ring2_String*
Mkx_Scribe_Hll_LiteralNode_getString
  (
    Mkx_Scribe_Hll_LiteralNode* self
  )
{ 
  if (Mkx_Scribe_Hll_Node_getKind(Ring1_cast(Mkx_Scribe_Hll_Node*, self)) != Mkx_Scribe_Hll_NodeType_String)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getString(&self->value);
}

Ring2_String*
Mkx_Scribe_Hll_LiteralNode_getName
  (
    Mkx_Scribe_Hll_LiteralNode* self
  )
{
  if (Mkx_Scribe_Hll_Node_getKind(Ring1_cast(Mkx_Scribe_Hll_Node*, self)) != Mkx_Scribe_Hll_NodeType_Name)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getString(&self->value);
}
