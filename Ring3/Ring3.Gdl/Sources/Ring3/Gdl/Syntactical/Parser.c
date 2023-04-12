/// @file Ring3/Gdl/Syntactical/Parser.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Syntactical/Parser.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"
#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Context.h"
#include "Ring3/Gdl/Lexical/DefaultScanner.h"
#include "Ring3/Gdl/Syntactical/Node.h"
#include "Ring3/Gdl/Literals/BooleanLiteral.h"
#include "Ring3/Gdl/Literals/IntegerLiteral.h"
#include "Ring3/Gdl/Literals/RealLiteral.h"
#include "Ring3/Gdl/Literals/StringLiteral.h"
#include "Ring3/Gdl/Literals/VoidLiteral.h"
#undef RING3_GDL_PRIVATE


static void
Machine_Gdl_Parser_visit
  (
    Machine_Gdl_Parser* self
  )
{
  if (self->scanner) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->scanner);
  }
}

static void
Machine_Gdl_Parser_construct
  (
    Machine_Gdl_Parser* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*,self), numberOfArguments, arguments);
  self->scanner = Ring1_cast(Ring3_Gdl_Scanner*,Ring3_Gdl_DefaultScanner_create(Ring2_String_fromC(false, "<empty input>"), Ring2_ByteBuffer_create()));
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Parser_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Parser /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_Gdl_Parser_visit /*visit*/,
                         &Machine_Gdl_Parser_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

Ring1_NoDiscardReturn() Machine_Gdl_Parser*
Machine_Gdl_Parser_create
  (
  )
{
  Machine_Type* ty = Machine_Gdl_Parser_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gdl_Parser* self = Ring1_cast(Machine_Gdl_Parser*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

#include "Ring3/Gdl/Syntactical/Parser-inlay.i"

static void
checkKind
  (
    Machine_Gdl_Parser* self,
    Ring3_Gdl_TokenKind expected
  )
{
  if (currentKind(self) != expected) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

static void
next
  (
    Machine_Gdl_Parser* self
  )
{ Ring3_Gdl_Scanner_step(self->scanner); }

/// <code>
/// name := NAME
/// </code>
static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseName
  (
    Machine_Gdl_Parser* self
  );

/// <code>
/// value := BOOLEAN | INTEGER | REAL | STRING | VOID
///        | list | map
/// </code>
static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseValue
  (
    Machine_Gdl_Parser* self
  );

/// <code>
/// list := '[' listElements ']'
/// </code>
static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseList
  (
    Machine_Gdl_Parser* self
  );

/// <code>
/// map := '{' mapElements '}'
/// </code>
static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseMap
  (
    Machine_Gdl_Parser* self
  );

static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseName
  (
    Machine_Gdl_Parser* self
  )
{
  if (currentKind(self) != Ring3_Gdl_TokenKind_Name) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
  Ring2_String* nameString = Ring3_Gdl_Token_getText(Ring3_Gdl_Scanner_getToken(self->scanner));
  Ring3_Gdl_Name *name = Ring3_Gdl_Name_create(nameString);
  Ring2_Value temporary = Ring2_Value_StaticInitializerObject((Machine_Object*)name);
  Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Name, &temporary);
  next(self);
  return node;
}

static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseValue
  (
    Machine_Gdl_Parser* self
  )
{
  switch (currentKind(self)) {
  case Ring3_Gdl_TokenKind_LeftSquareBracket: {
    return parseList(self);
  } break;
  case Ring3_Gdl_TokenKind_LeftCurlyBracket: {
    return parseMap(self);
  } break;
  case Ring3_Gdl_TokenKind_Boolean: {
    Ring2_String* literalString = Ring3_Gdl_Token_getText(Ring3_Gdl_Scanner_getToken(self->scanner));
    Ring3_Gdl_BooleanLiteral* literal = Ring3_Gdl_BooleanLiteral_create(literalString);
    Ring2_Value temporary = Ring2_Value_StaticInitializerObject((Machine_Object*)literal);
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Boolean, &temporary);
    next(self);
    return node;
  } break;
  case Ring3_Gdl_TokenKind_Integer: {
    Ring2_String* literalString = Ring3_Gdl_Token_getText(Ring3_Gdl_Scanner_getToken(self->scanner));
    Ring3_Gdl_IntegerLiteral* literal = Ring3_Gdl_IntegerLiteral_create(literalString);
    Ring2_Value temporary = Ring2_Value_StaticInitializerObject((Machine_Object*)literal);
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Integer, &temporary);
    next(self);
    return node;
  } break;
  case Ring3_Gdl_TokenKind_Real: {
    Ring2_String* literalString = Ring3_Gdl_Token_getText(Ring3_Gdl_Scanner_getToken(self->scanner));
    Ring3_Gdl_RealLiteral* literal = Ring3_Gdl_RealLiteral_create(literalString);
    Ring2_Value temporary = Ring2_Value_StaticInitializerObject((Machine_Object*)literal);
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Real, &temporary);
    next(self);
    return node;
  } break;
  case Ring3_Gdl_TokenKind_String: {
    Ring2_String* literalString = Ring3_Gdl_Token_getText(Ring3_Gdl_Scanner_getToken(self->scanner));
    Ring3_Gdl_StringLiteral* literal = Ring3_Gdl_StringLiteral_create(literalString);
    Ring2_Value temporary = Ring2_Value_StaticInitializerObject((Machine_Object*)literal);
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_String, &temporary);
    next(self);
    return node;
  } break;
  case Ring3_Gdl_TokenKind_Void: {
    Ring2_String* literalString = Ring3_Gdl_Token_getText(Ring3_Gdl_Scanner_getToken(self->scanner));
    Ring3_Gdl_VoidLiteral* literal = Ring3_Gdl_VoidLiteral_create(literalString);
    Ring2_Value temporary = Ring2_Value_StaticInitializerObject((Machine_Object*)literal);
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Void, &temporary);
    next(self);
    return node;
  } break;
  default:
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  };
}

static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parsePair
  (
    Machine_Gdl_Parser* self
  )
{
  Ring2_Value temporary;
  Ring2_Value_setVoid(&temporary, Ring2_Void_Void);
  Machine_Gdl_Node* pairNode = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Pair, &temporary);
  Machine_Gdl_Node* keyNode = parseName(self);
  {
    Ring2_Value_setObject(&temporary, (Machine_Object*)keyNode);
    Ring2_Collections_List_append(pairNode->children, temporary);
  }
  checkKind(self, Ring3_Gdl_TokenKind_Colon);
  next(self);
  Machine_Gdl_Node* valueNode = parseValue(self);
  {
    Ring2_Value_setObject(&temporary, (Machine_Object*)valueNode);
    Ring2_Collections_List_append(pairNode->children, temporary);
  }
  return pairNode;
}

static Ring1_NoDiscardReturn() Machine_Gdl_Node *
parseList
  (
    Machine_Gdl_Parser* self
  )
{
  next(self);
  Ring2_Value temporary;
  Ring2_Value_setVoid(&temporary, Ring2_Void_Void);
  Machine_Gdl_Node* parent = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_List, &temporary);
  while (currentKind(self) != Ring3_Gdl_TokenKind_EndOfInput && currentKind(self) != Ring3_Gdl_TokenKind_RightSquareBracket) {
    Machine_Gdl_Node* child = parseValue(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
    if (currentKind(self) == Ring3_Gdl_TokenKind_Comma) {
      next(self);
    }
  }
  checkKind(self, Ring3_Gdl_TokenKind_RightSquareBracket);
  next(self);
  return parent;
}

static Ring1_NoDiscardReturn() Machine_Gdl_Node*
parseMap
  (
    Machine_Gdl_Parser* self
  )
{
  next(self);
  Ring2_Value temporary;
  Ring2_Value_setVoid(&temporary, Ring2_Void_Void);
  Machine_Gdl_Node* parent = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Map, &temporary);
  while (currentKind(self) != Ring3_Gdl_TokenKind_EndOfInput && currentKind(self) != Ring3_Gdl_TokenKind_RightCurlyBracket) {
    Machine_Gdl_Node* child = parsePair(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
    if (currentKind(self) == Ring3_Gdl_TokenKind_Comma) {
      next(self);
    }
  }
  checkKind(self, Ring3_Gdl_TokenKind_RightCurlyBracket);
  next(self);
  return parent;
}

Ring1_NoDiscardReturn() Machine_Gdl_Node*
Machine_Gdl_Parser_parse
  (
    Machine_Gdl_Parser* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  )
{
  Ring3_Gdl_Scanner_setInput(self->scanner, inputName, inputBytes);
  checkKind(self, Ring3_Gdl_TokenKind_StartOfInput);
  next(self);
  Ring2_Value temporary = Ring2_Value_StaticInitializerString(inputName);
  Machine_Gdl_Node *parent = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_CompilationUnit, &temporary);
  switch (currentKind(self)) {
  case Ring3_Gdl_TokenKind_LeftSquareBracket: {
    Machine_Gdl_Node* child = parseList(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
  } break;
  case Ring3_Gdl_TokenKind_LeftCurlyBracket: {
    Machine_Gdl_Node* child = parseMap(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
  } break;
  default:
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  };
  return parent;
}
