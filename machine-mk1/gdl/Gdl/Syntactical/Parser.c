/// @file Gdl/Syntactical/Parser.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gdl/Syntactical/Parser.h"

#include <string.h>

static void Machine_GDL_Parser_visit(Machine_GDL_Parser* self) {
  if (self->scanner) {
    Machine_Gc_visit(self->scanner);
  }
}

static void Machine_GDL_Parser_construct(Machine_GDL_Parser* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->scanner = Machine_GDL_Scanner_create(Machine_String_create("<empty input>", strlen("<empty input>")), Machine_ByteBuffer_create());
  Machine_setClassType((Machine_Object*)self, Machine_GDL_Parser_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_GDL_Parser, Machine_Object, &Machine_GDL_Parser_visit,
                         &Machine_GDL_Parser_construct, NULL, NULL, NULL)

Machine_GDL_Parser* Machine_GDL_Parser_create() {
  Machine_ClassType* ty = Machine_GDL_Parser_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GDL_Parser* self = (Machine_GDL_Parser*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

#include "./../../GDL/Syntactical/Parser-inlay.i"

static void checkKind(Machine_GDL_Parser* self, Machine_GDL_TokenKind expected) {
  if (currentKind(self) != expected) {
    Machine_setStatus(Machine_Status_SyntacticalError);
    Machine_jump();
  }
}

static void next(Machine_GDL_Parser* self) {
  Machine_GDL_Scanner_step(self->scanner);
}

/// <code>
/// key := BOOLEAN | NAME | VOID
/// </code>
static Machine_GDL_Node* parseKey(Machine_GDL_Parser* self);


/// <code>
/// key := INTEGER | REAL
///      | BOOLEAN | NAME | VOID
///      | list | map
/// </code>
static Machine_GDL_Node* parseValue(Machine_GDL_Parser* self);

/// <code>
/// list := '[' ']'
/// </code>
static Machine_GDL_Node* parseList(Machine_GDL_Parser* self);

/// <code>
/// map := '{' '}'
/// </code>
static Machine_GDL_Node* parseMap(Machine_GDL_Parser* self);


static Machine_GDL_Node* parseKey(Machine_GDL_Parser* self) {
  Machine_GDL_TokenKind x = currentKind(self);
  if (x != Machine_GDL_TokenKind_Boolean && x != Machine_GDL_TokenKind_Name && x != Machine_GDL_TokenKind_Void) {
    Machine_setStatus(Machine_Status_SyntacticalError);
    Machine_jump();
  }
  Machine_GDL_Node* node = Machine_GDL_Node_create(Machine_GDL_NodeKind_Key, Machine_GDL_Scanner_getTokenText(self->scanner));
  next(self);
  return node;
}

static Machine_GDL_Node* parseValue(Machine_GDL_Parser* self) {
  switch (currentKind(self)) {
  case Machine_GDL_TokenKind_LeftSquareBracket: {
    return parseList(self);
  } break;
  case Machine_GDL_TokenKind_LeftCurlyBracket: {
    return parseMap(self);
  } break;
  case Machine_GDL_TokenKind_Boolean: {
    Machine_GDL_Node* node = Machine_GDL_Node_create(Machine_GDL_NodeKind_Boolean, Machine_GDL_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_GDL_TokenKind_Integer: {
    Machine_GDL_Node* node = Machine_GDL_Node_create(Machine_GDL_NodeKind_Integer, Machine_GDL_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_GDL_TokenKind_Real: {
    Machine_GDL_Node* node = Machine_GDL_Node_create(Machine_GDL_NodeKind_Real, Machine_GDL_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_GDL_TokenKind_String: {
    Machine_GDL_Node* node = Machine_GDL_Node_create(Machine_GDL_NodeKind_String, Machine_GDL_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  case Machine_GDL_TokenKind_Void: {
    Machine_GDL_Node* node = Machine_GDL_Node_create(Machine_GDL_NodeKind_Void, Machine_GDL_Scanner_getTokenText(self->scanner));
    next(self);
    return node;
  } break;
  default:
    Machine_setStatus(Machine_Status_SyntacticalError);
    Machine_jump();
  };
}

static Machine_GDL_Node* parsePair(Machine_GDL_Parser* self) {
  Machine_Value temporary;

  Machine_GDL_Node* pairNode = Machine_GDL_Node_create(Machine_GDL_NodeKind_Pair, NULL);
  Machine_GDL_Node* keyNode = parseKey(self);
  {
    Machine_Value_setObject(&temporary, (Machine_Object*)keyNode);
    Machine_List_append(pairNode->children, temporary);
  }
  checkKind(self, Machine_GDL_TokenKind_Colon);
  next(self);
  Machine_GDL_Node* valueNode = parseValue(self);
  {
    Machine_Value_setObject(&temporary, (Machine_Object*)valueNode);
    Machine_List_append(pairNode->children, temporary);
  }
  return pairNode;
}

static Machine_GDL_Node *parseList(Machine_GDL_Parser* self) {
  next(self);
  Machine_GDL_Node* parent = Machine_GDL_Node_create(Machine_GDL_NodeKind_List, NULL);
  while (currentKind(self) != Machine_GDL_TokenKind_EndOfInput && currentKind(self) != Machine_GDL_TokenKind_RightSquareBracket) {
    Machine_GDL_Node* child = parseValue(self);
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)child);
    Machine_List_append(parent->children, temporary);
    if (currentKind(self) == Machine_GDL_TokenKind_Comma) {
      next(self);
    }
  }
  checkKind(self, Machine_GDL_TokenKind_RightSquareBracket);
  next(self);
  return parent;
}

static Machine_GDL_Node* parseMap(Machine_GDL_Parser* self) {
  next(self);
  Machine_GDL_Node* parent = Machine_GDL_Node_create(Machine_GDL_NodeKind_Map, NULL);
  while (currentKind(self) != Machine_GDL_TokenKind_EndOfInput && currentKind(self) != Machine_GDL_TokenKind_RightCurlyBracket) {
    Machine_GDL_Node* child = parsePair(self);
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)child);
    Machine_List_append(parent->children, temporary);
    if (currentKind(self) == Machine_GDL_TokenKind_Comma) {
      next(self);
    }
  }
  checkKind(self, Machine_GDL_TokenKind_RightCurlyBracket);
  next(self);
  return parent;
}

Machine_GDL_Node* Machine_GDL_Parser_parse(Machine_GDL_Parser* self, Machine_String* inputName, Machine_ByteBuffer* inputBytes) {
  Machine_GDL_Scanner_setInput(self->scanner, inputName, inputBytes);
  checkKind(self, Machine_GDL_TokenKind_StartOfInput);
  next(self);
  Machine_GDL_Node *parent = Machine_GDL_Node_create(Machine_GDL_NodeKind_CompilationUnit, inputName);
  switch (currentKind(self)) {
  case Machine_GDL_TokenKind_LeftSquareBracket: {
    Machine_GDL_Node* child = parseList(self);
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)child);
    Machine_List_append(parent->children, temporary);
  } break;
  case Machine_GDL_TokenKind_LeftCurlyBracket: {
    Machine_GDL_Node* child = parseMap(self);
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)child);
    Machine_List_append(parent->children, temporary);
  } break;
  default:
    Machine_setStatus(Machine_Status_SyntacticalError);
    Machine_jump();
  };
  return parent;
}
