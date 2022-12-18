/// @file Ring3/Gdl/Syntactical/Parser.c
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Syntactical/Parser.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"
#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Context.h"
#include "Ring3/Gdl/Lexical/Scanner.h"
#include "Ring3/Gdl/Syntactical/Node.h"
#undef RING3_GDL_PRIVATE


static void Machine_Gdl_Parser_visit(Machine_Gdl_Parser* self) {
  if (self->scanner) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->scanner);
  }
}

static void Machine_Gdl_Parser_construct(Machine_Gdl_Parser* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->scanner = Machine_Gdl_Scanner_create(Ring2_String_fromC("<empty input>"), Ring2_ByteBuffer_create());
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Parser_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Parser, Machine_Object, &Machine_Gdl_Parser_visit,
                         &Machine_Gdl_Parser_construct, NULL, NULL, NULL)

Machine_Gdl_Parser* Machine_Gdl_Parser_create() {
  Machine_ClassType* ty = Machine_Gdl_Parser_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Gdl_Parser* self = (Machine_Gdl_Parser*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

#include "Ring3/Gdl/Syntactical/Parser-inlay.i"

static void checkKind(Machine_Gdl_Parser* self, Machine_Gdl_TokenKind expected) {
  if (currentKind(self) != expected) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

static void next(Machine_Gdl_Parser* self) {
  Machine_Gdl_Scanner_step(self->scanner);
}

/// <code>
/// key := BOOLEAN | NAME | VOID
/// </code>
static Machine_Gdl_Node* parseKey(Machine_Gdl_Parser* self);


/// <code>
/// key := INTEGER | REAL
///      | BOOLEAN | NAME | VOID
///      | list | map
/// </code>
static Machine_Gdl_Node* parseValue(Machine_Gdl_Parser* self);

/// <code>
/// list := '[' ']'
/// </code>
static Machine_Gdl_Node* parseList(Machine_Gdl_Parser* self);

/// <code>
/// map := '{' '}'
/// </code>
static Machine_Gdl_Node* parseMap(Machine_Gdl_Parser* self);


static Machine_Gdl_Node* parseKey(Machine_Gdl_Parser* self) {
  Machine_Gdl_TokenKind x = currentKind(self);
  if (x != Machine_Gdl_TokenKind_Boolean && x != Machine_Gdl_TokenKind_Name && x != Machine_Gdl_TokenKind_Void) {
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
  Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Key, Machine_Gdl_Scanner_getTokenText(self->scanner));
  next(self);
  return node;
}

static Machine_Gdl_Node* parseValue(Machine_Gdl_Parser* self) {
  switch (currentKind(self)) {
  case Machine_Gdl_TokenKind_LeftSquareBracket: {
    return parseList(self);
  } break;
  case Machine_Gdl_TokenKind_LeftCurlyBracket: {
    return parseMap(self);
  } break;
  case Machine_Gdl_TokenKind_Boolean: {
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Boolean, Machine_Gdl_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_Gdl_TokenKind_Integer: {
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Integer, Machine_Gdl_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_Gdl_TokenKind_Real: {
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Real, Machine_Gdl_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_Gdl_TokenKind_String: {
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_String, Machine_Gdl_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_Gdl_TokenKind_Void: {
    Machine_Gdl_Node* node = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Void, Machine_Gdl_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  default:
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  };
}

static Machine_Gdl_Node* parsePair(Machine_Gdl_Parser* self) {
  Ring2_Value temporary;

  Machine_Gdl_Node* pairNode = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Pair, NULL);
  Machine_Gdl_Node* keyNode = parseKey(self);
  {
    Ring2_Value_setObject(&temporary, (Machine_Object*)keyNode);
    Ring2_Collections_List_append(pairNode->children, temporary);
  }
  checkKind(self, Machine_Gdl_TokenKind_Colon);
  next(self);
  Machine_Gdl_Node* valueNode = parseValue(self);
  {
    Ring2_Value_setObject(&temporary, (Machine_Object*)valueNode);
    Ring2_Collections_List_append(pairNode->children, temporary);
  }
  return pairNode;
}

static Machine_Gdl_Node *parseList(Machine_Gdl_Parser* self) {
  next(self);
  Machine_Gdl_Node* parent = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_List, NULL);
  while (currentKind(self) != Machine_Gdl_TokenKind_EndOfInput && currentKind(self) != Machine_Gdl_TokenKind_RightSquareBracket) {
    Machine_Gdl_Node* child = parseValue(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
    if (currentKind(self) == Machine_Gdl_TokenKind_Comma) {
      next(self);
    }
  }
  checkKind(self, Machine_Gdl_TokenKind_RightSquareBracket);
  next(self);
  return parent;
}

static Machine_Gdl_Node* parseMap(Machine_Gdl_Parser* self) {
  next(self);
  Machine_Gdl_Node* parent = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Map, NULL);
  while (currentKind(self) != Machine_Gdl_TokenKind_EndOfInput && currentKind(self) != Machine_Gdl_TokenKind_RightCurlyBracket) {
    Machine_Gdl_Node* child = parsePair(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
    if (currentKind(self) == Machine_Gdl_TokenKind_Comma) {
      next(self);
    }
  }
  checkKind(self, Machine_Gdl_TokenKind_RightCurlyBracket);
  next(self);
  return parent;
}

Machine_Gdl_Node* Machine_Gdl_Parser_parse(Machine_Gdl_Parser* self, Ring2_String* inputName, Ring2_ByteBuffer* inputBytes) {
  Machine_Gdl_Scanner_setInput(self->scanner, inputName, inputBytes);
  checkKind(self, Machine_Gdl_TokenKind_StartOfInput);
  next(self);
  Machine_Gdl_Node *parent = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_CompilationUnit, inputName);
  switch (currentKind(self)) {
  case Machine_Gdl_TokenKind_LeftSquareBracket: {
    Machine_Gdl_Node* child = parseList(self);
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)child);
    Ring2_Collections_List_append(parent->children, temporary);
  } break;
  case Machine_Gdl_TokenKind_LeftCurlyBracket: {
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
