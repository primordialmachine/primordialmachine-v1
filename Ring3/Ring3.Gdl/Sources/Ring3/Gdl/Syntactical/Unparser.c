/// @file Ring3/Gdl/Syntactical/Unparser.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Syntactical/Unparser.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"
#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Context.h"
#include "Ring3/Gdl/Syntactical/Node.h"
#undef RING3_GDL_PRIVATE


static void
Machine_Gdl_Unparser_visit
  (
    Machine_Gdl_Unparser* self
    )
{ 
  if (self->colon) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->colon);
  }
  if (self->comma) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->comma);
  }
  if (self->leftCurlyBracket) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->leftCurlyBracket);
  }
  if (self->leftSquareBracket) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->leftSquareBracket);
  }
  if (self->newLine) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->newLine);
  }
  if (self->rightCurlyBracket) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rightCurlyBracket);
  }
  if (self->rightSquareBracket) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rightSquareBracket);
  }
  if (self->space) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->space);
  }
}

static void
Machine_Gdl_Unparser_construct
  (
    Machine_Gdl_Unparser* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  self->colon = Ring2_String_fromC(false, ":");
  self->comma = Ring2_String_fromC(false, ",");
  self->leftCurlyBracket = Ring2_String_fromC(false, "{");
  self->leftSquareBracket = Ring2_String_fromC(false, "[");
  self->newLine = Ring2_String_fromC(false, "\n");
  self->rightCurlyBracket = Ring2_String_fromC(false, "}");
  self->rightSquareBracket = Ring2_String_fromC(false, "]");
  self->space = Ring2_String_fromC(false, " ");

  self->indent = 0;

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Unparser_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Unparser /*type*/,
                         Machine_Object /*parenType*/,
                         &Machine_Gdl_Unparser_visit /*visit*/,
                         &Machine_Gdl_Unparser_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

Ring1_NoDiscardReturn() Machine_Gdl_Unparser*
Machine_Gdl_Unparser_create
  (
  )
{
  Machine_Type* ty = Machine_Gdl_Unparser_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gdl_Unparser* self = Ring1_cast(Machine_Gdl_Unparser*,
                                          Machine_allocateClassObject(ty,
                                                                      NUMBER_OF_ARGUMENTS,
                                                                      ARGUMENTS));
  return self;
}

static void
onIndent
  (
    Machine_Gdl_Unparser *self,
    Ring2_String* outputName,
    Ring2_StringBuffer* outputStringBuffer
  )
{
  for (int64_t i = 0, n = self->indent * 2; i < n; ++i) {
    Ring2_StringBuffer_appendString(outputStringBuffer, self->space);  
  }
}

static void
onNode
  (
    Machine_Gdl_Unparser *self,
    Machine_Gdl_Node *node,
    Ring2_String* outputName,
    Ring2_StringBuffer* outputStringBuffer
  )
{
  switch (Machine_Gdl_Node_getKind(node)) {
  case Machine_Gdl_NodeKind_Boolean: {
    Ring3_Gdl_BooleanLiteral* literal = (Ring3_Gdl_BooleanLiteral*)Ring2_Value_getObject(&node->value);
    Ring2_StringBuffer_appendString(outputStringBuffer, Ring3_Gdl_BooleanLiteral_toString(literal));
  } break;
  case Machine_Gdl_NodeKind_CompilationUnit: {
    if (Machine_Gdl_Node_getSize(node) != 1) {
      Ring1_Status_set(Ring1_Status_InvalidSyntactics);
      Ring2_jump();
    }
    onNode(self, Machine_Gdl_Node_getAt(node, 0), outputName, outputStringBuffer);
  } break;
  case Machine_Gdl_NodeKind_Integer: {
    Ring3_Gdl_IntegerLiteral* literal = (Ring3_Gdl_IntegerLiteral*)Ring2_Value_getObject(&node->value);
    Ring2_StringBuffer_appendString(outputStringBuffer, Ring3_Gdl_IntegerLiteral_toString(literal));
  } break;
  case Machine_Gdl_NodeKind_List: {
    Ring2_StringBuffer_appendString(outputStringBuffer, self->leftSquareBracket);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->newLine);
    self->indent += 1;
    if (Machine_Gdl_Node_getSize(node) == 0) {
      //Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    } else if (Machine_Gdl_Node_getSize(node) == 1) {
      Machine_Gdl_Node *element = Machine_Gdl_Node_getAt(node, 0);
      //Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
      onNode(self, element, outputName, outputStringBuffer);
      //Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    } else {
      Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
      for (int64_t i = 0, n = Machine_Gdl_Node_getSize(node) - 1; i < n; ++i) {
        Machine_Gdl_Node *key = Machine_Gdl_Node_getAt(node, 0);
        onNode(self, key, outputName, outputStringBuffer);
        Ring2_StringBuffer_appendString(outputStringBuffer, self->comma);
        Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
      }
      Machine_Gdl_Node *key = Machine_Gdl_Node_getAt(node, Machine_Gdl_Node_getSize(node) - 1);
      Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    }
    self->indent -= 1;
    onIndent(self, outputName, outputStringBuffer);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->rightSquareBracket);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->newLine);
  } break;
  case Machine_Gdl_NodeKind_Map: {
    Ring2_StringBuffer_appendString(outputStringBuffer, self->leftCurlyBracket);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->newLine);
    self->indent += 1;
    if (Machine_Gdl_Node_getSize(node) == 0) {
      //Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    } else if (Machine_Gdl_Node_getSize(node) == 1) {
      Machine_Gdl_Node *pair = Machine_Gdl_Node_getAt(node, 0);
      //Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
      onNode(self, pair, outputName, outputStringBuffer);
      //Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    } else {
      Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
      for (int64_t i = 0, n = Machine_Gdl_Node_getSize(node) - 1; i < n; ++i) {
        Machine_Gdl_Node *pair = Machine_Gdl_Node_getAt(node, 0);
        onNode(self, pair, outputName, outputStringBuffer);
        Ring2_StringBuffer_appendString(outputStringBuffer, self->comma);
        Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
      }
      Machine_Gdl_Node *pair = Machine_Gdl_Node_getAt(node, Machine_Gdl_Node_getSize(node) - 1);
      onNode(self, pair, outputName, outputStringBuffer);
      Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    }
    self->indent -= 1;
    onIndent(self, outputName, outputStringBuffer);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->rightCurlyBracket);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->newLine);
  } break;
  case Machine_Gdl_NodeKind_Name: {
    Ring3_Gdl_Name* name = (Ring3_Gdl_Name*)Ring2_Value_getObject(&node->value);
    Ring2_StringBuffer_appendString(outputStringBuffer, Ring3_Gdl_Name_toString(name));
  } break;
  case Machine_Gdl_NodeKind_Pair: {
    Machine_Gdl_Node *key = Machine_Gdl_Node_getAt(node, 0);
    Machine_Gdl_Node *value = Machine_Gdl_Node_getAt(node, 1);
    onIndent(self, outputName, outputStringBuffer);
    onNode(self, key, outputName, outputStringBuffer);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->colon);
    Ring2_StringBuffer_appendString(outputStringBuffer, self->space);
    onNode(self, value, outputName, outputStringBuffer);
  } break;
  case Machine_Gdl_NodeKind_Real: {
    Ring3_Gdl_RealLiteral* literal = (Ring3_Gdl_RealLiteral*)Ring2_Value_getObject(&node->value);
    Ring2_StringBuffer_appendString(outputStringBuffer, Ring3_Gdl_RealLiteral_toString(literal));
  } break;
  case Machine_Gdl_NodeKind_String: {
    Ring2_String* quotes = Ring2_String_fromC(false, "\"");
    Ring2_StringBuffer_appendString(outputStringBuffer, quotes);
    Ring3_Gdl_StringLiteral* literal = (Ring3_Gdl_StringLiteral*)Ring2_Value_getObject(&node->value);
    Ring2_StringBuffer_appendString(outputStringBuffer, Ring3_Gdl_StringLiteral_toString(literal, true));
    Ring2_StringBuffer_appendString(outputStringBuffer, quotes);
  } break;
  case Machine_Gdl_NodeKind_Void: {
    Ring3_Gdl_VoidLiteral* literal = (Ring3_Gdl_VoidLiteral*)Ring2_Value_getObject(&node->value);
    Ring2_StringBuffer_appendString(outputStringBuffer, Ring3_Gdl_VoidLiteral_toString(literal));
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  } break;
  };
}

void
Machine_Gdl_Unparser_unparse
  (
    Machine_Gdl_Unparser* self,
    Machine_Gdl_Node *node,
    Ring2_String* outputName,
    Ring2_StringBuffer* outputStringBuffer
  )
{
  onNode(self, node, outputName, outputStringBuffer);
}
