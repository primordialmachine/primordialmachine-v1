// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/EnvironmentParser.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Environment/EnvironmentParser.h"

#include "Ring2/Operations.h"

static void
Mkx_Template_EnvironmentParser_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_EnvironmentParser* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Template_EnvironmentParser, Machine_Object,
                         &Mkx_Template_EnvironmentParser_visit,
                         &Mkx_Template_EnvironmentParser_construct,
                         NULL, NULL, NULL)

static void
Mkx_Template_EnvironmentParser_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_EnvironmentParser* self
  )
{
  if (self->scanner) {
    Ring2_Gc_visit(gc, self->scanner);
  }
}

void
Mkx_Template_EnvironmentParser_construct
  (
    Mkx_Template_EnvironmentParser *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->scanner = (Mkx_Template_EnvironmentScanner *)Ring2_Value_getObject(&arguments[0]);
  Machine_setClassType((Machine_Object*)self, Mkx_Template_EnvironmentParser_getType());
}

Mkx_Template_EnvironmentParser*
Mkx_Template_EnvironmentParser_create
  (
    Mkx_Template_EnvironmentScanner* scanner
  )
{
  Machine_Type* ty = Mkx_Template_EnvironmentParser_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,scanner));
  Mkx_Template_EnvironmentParser *self = Ring1_cast(Mkx_Template_EnvironmentParser*,
                                                    Machine_allocateClassObject(ty,
                                                                                NUMBER_OF_ARGUMENTS,
                                                                                arguments));
  return self;
}

#define TYPE Mkx_Template_EnvironmentParser
#define PARENT(expression) Ring1_cast(Mkx_Scribe_Node*,expression)
#include "Mkx/Scribe/Hll/Parselets.Core.i"
#undef PARENT
#undef TYPE

Ring1_NoReturn() static void
errorf
  (
    Ring2_Context* context,
    Mkx_Scribe_Position* position,
    Ring2_String* format,
    ...
  )
{
  Ring2_String* prefix, * suffix;

  // Make prefix.
  prefix = Ring2_String_printf(context,
                               Ring2_String_fromC(false, "%s: %i: "),
                               Mkx_Scribe_Position_getPathName(position),
                               Mkx_Scribe_Position_getLineNumber(position));

  // Make suffix.
  Ring2_JumpTarget jumpTarget;
  va_list arguments;
  va_start(arguments, format);
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment))
  {
    suffix = Ring2_String_printv(Ring2_Context_get(), format, arguments);
    Ring2_popJumpTarget();
    va_end(arguments);
  }
  else
  {
    Ring2_popJumpTarget();
    va_end(arguments);
    Ring2_jump();
  }

  // Emit prefix suffix.
  Ring2_emitf(context, Ring2_String_fromC(false, "%s%s\n"), prefix, suffix);
  Ring1_Status_set(Ring1_Status_InvalidSyntactics);
  Ring2_jump();
}

// <code>
// value := STRING+ | INTEGER
// </code>
static Mkx_Scribe_Hll_Node*
parseValue
  (
    Mkx_Template_EnvironmentParser* self
  )
{
  if (is(self, Mkx_Scribe_Hll_TokenType_String))
  {
    Mkx_Scribe_Position* position = getTokenPosition(self);
    Ring2_String* text = getTokenText(self);
    next(self);
    while (is(self, Mkx_Scribe_Hll_TokenType_String))
    {
      Ring2_String* temporary = getTokenText(self);
      text = Ring2_String_concatenate(Ring2_Context_get(), text, temporary);
      next(self);
    }
    return Mkx_Scribe_Hll_Node_createStringLiteral(position, text);
  }
  else if (is(self, Mkx_Scribe_Hll_TokenType_Integer))
  {
    Ring2_String* valueString = getTokenText(self);
    next(self);
    return Mkx_Scribe_Hll_Node_createIntegerLiteral(getTokenPosition(self), valueString);
  }
  else
  {
    errorf(Ring2_Context_get(), getTokenPosition(self), Ring2_String_fromC(false, "expected <STRING> or <INTEGER>"));
  }
}

// <code>
// name := (NAME|STRING)
// </code>
static Mkx_Scribe_Hll_Node*
parseName
  (
    Mkx_Template_EnvironmentParser* self
  )
{
  if (!is(self, Mkx_Scribe_Hll_TokenType_String) && !is(self, Mkx_Scribe_Hll_TokenType_Name))
  {
    errorf(Ring2_Context_get(), getTokenPosition(self), Ring2_String_fromC(false, "expected <STRING> or <NAME>"));
  }
  /// @todo Should be Mkx_Scribe_Hll_Node_createStringLiteral if token type is a string and
  /// Mkx_Scribe_Hll_Node_createNameLiteral if token type is a name.
  Mkx_Scribe_Hll_Node* node = Mkx_Scribe_Hll_Node_createStringLiteral(getTokenPosition(self), getTokenText(self));
  next(self);
  return node;
}

// <code>
// element := name ':' value
// </code>
static void
parseElement
  (
    Mkx_Template_EnvironmentParser* self,
    Mkx_Scribe_Hll_Node** nameNode,
    Mkx_Scribe_Hll_Node** valueNode
  )
{
  // name
  *nameNode = parseName(self);
  // ':'
  if (!is(self, Mkx_Scribe_Hll_TokenType_Colon))
  {
    errorf(Ring2_Context_get(), getTokenPosition(self), Ring2_String_fromC(false, "expected ':'"));
  }
  next(self);
  // value
  *valueNode = parseValue(self);
}

/// <code>
/// environment := element (',' element)* | epsilon
/// </code>
static Mkx_Scribe_Hll_Node*
parseEnvironment
  (
    Mkx_Template_EnvironmentParser* self
  )
{
  Mkx_Scribe_Hll_Node* createTableNode = Mkx_Scribe_Hll_Node_createCreateTable(getTokenPosition(self));
  // `startOfInput`
  if (!is(self, Mkx_Scribe_Hll_TokenType_StartOfInput))
  {
    errorf(Ring2_Context_get(), getTokenPosition(self), Ring2_String_fromC(false, "expected <start of input>"));
  }
  next(self);
  // `element (',' element)*` | epsilon
  while (!is(self, Mkx_Scribe_Hll_TokenType_EndOfInput))
  {
    Mkx_Scribe_Hll_Node* nameNode, * valueNode;
    parseElement(self, &nameNode, &valueNode);
    Mkx_Scribe_Hll_Node_append(createTableNode, nameNode);
    Mkx_Scribe_Hll_Node_append(createTableNode, valueNode);
    if (is(self, Mkx_Scribe_Hll_TokenType_Comma))
    {
      next(self);
    }
    else
    {
      break;
    }
  }
  if (!is(self, Mkx_Scribe_Hll_TokenType_EndOfInput))
  {
    errorf(Ring2_Context_get(), getTokenPosition(self), Ring2_String_fromC(false, "expected <end of input>"));
  }

  return createTableNode;
}

Mkx_Scribe_Hll_Node*
Mkx_Template_EnvironmentParser_run
  (
    Mkx_Template_EnvironmentParser* self
  )
{ return parseEnvironment(self); }
