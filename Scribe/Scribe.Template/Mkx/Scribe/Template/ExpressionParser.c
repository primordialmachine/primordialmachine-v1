#include "Mkx/Scribe/Template/ExpressionParser.h"


#include "Mkx/Scribe/Template/ExpressionScanner.h"
#include "Mkx/Scribe/Hll.h"
#define TYPE Mkx_Template_ExpressionParser
#define PARENT(expression) ((Mkx_Scribe_Node *)(expression))
#include "Mkx/Scribe/Hll/Parselets.Core.i"
#undef TYPE


static void
Mkx_Template_ExpressionParser_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_ExpressionParser* self
  );

static void
Mkx_Template_ExpressionParser_constructClass
  (
    Mkx_Template_ExpressionParser_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Template_ExpressionParser, Machine_Object,
                         &Mkx_Template_ExpressionParser_visit, 
                         &Mkx_Template_ExpressionParser_construct,
                         NULL,
                         &Mkx_Template_ExpressionParser_constructClass,
                         NULL)

/// <code>
/// argumentList := '(' ')'
/// </code>
static Mkx_Scribe_Hll_Node*
parseArgumentList
  (
    Mkx_Template_ExpressionParser* self
  );

/// <code>
/// prefixExpression := NAME argumentList?
///                   | '(' additiveExpression ')'
/// </code>
static Mkx_Scribe_Hll_Node *
parsePrefixExpression
  (
    Mkx_Template_ExpressionParser* self
  );

/// <code>
/// constantExpression := INTEGER|STRING
/// </code>
static Mkx_Scribe_Hll_Node*
parseConstantExpression
  (
    Mkx_Template_ExpressionParser* self
  );

/// <code>
/// additiveExpression := multiplicativeExpression (('+'|'-') multiplicativeExpression)*
/// </code>
static Mkx_Scribe_Hll_Node*
parseAdditiveExpression
  (
    Mkx_Template_ExpressionParser* self
  );

/// <code>
/// multiplicativeExpression := callExpression (('*'|'/') callExpression)*
/// </code>
static Mkx_Scribe_Hll_Node*
parseMultiplicativeExpression
  (
    Mkx_Template_ExpressionParser* self
  );

/// <code>
/// simpleExpression := prefixExpression
///                   | constantExpression
///                   | '+' simpleExpression
///                   | '-' simpleExpression
/// </code>
static Mkx_Scribe_Hll_Node*
parseSimpleExpression
  (
    Mkx_Template_ExpressionParser* self
  );

static void
expectedStringLiteralError
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s: %i: expected <string literal>. Received %s\n");
  Ring2_emitf(Ring2_Context_get(), format, getTokenPathname(self), getTokenLineNumber(self),
              Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
  Ring1_Status_set(Ring1_Status_InvalidSyntactics);
  Ring2_jump();
}

Ring1_NoReturn() static void
internalError
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s: %i: internal error. Received %s.\n");
  Ring2_emitf(Ring2_Context_get(), format, getTokenPathname(self), getTokenLineNumber(self),
              Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
  Ring1_Status_set(Ring1_Status_InternalError);
  Ring2_jump();
}

Ring1_NoReturn() static void
unclosedStringLiteralError
  (
    Mkx_Template_ExpressionParser*self
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s: %i: unclosed string literal. Received %s.\n");
  Ring2_emitf(Ring2_Context_get(), format, getTokenPathname(self), getTokenLineNumber(self),
              Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
  Ring1_Status_set(Ring1_Status_InvalidLexics);
  Ring2_jump();
}

Ring1_NoReturn() static void
unclosedExpressionError
  (
    Mkx_Template_ExpressionParser*self
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s: %i: unclosed expression. Received %s.\n");
  Ring2_emitf(Ring2_Context_get(), format, getTokenPathname(self), getTokenLineNumber(self),
              Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
  Ring1_Status_set(Ring1_Status_InvalidSyntactics);
  Ring2_jump();
}

Ring1_NoReturn() static void
unclosedParenthesesError
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s: %i: unclosed parentheses. Received %s.\n");
  Ring2_emitf(Ring2_Context_get(), format, getTokenPathname(self), getTokenLineNumber(self),
              Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
  Ring1_Status_set(Ring1_Status_InvalidSyntactics);
  Ring2_jump();
}

Ring1_NoReturn() static void
unclosedArgumentListError
  ( 
    Mkx_Template_ExpressionParser* self
  )
{
  Ring2_String* format = Ring2_String_fromC(false, "%s: %i: unclosed argument list. Received %s.\n");
  Ring2_emitf(Ring2_Context_get(), format, getTokenPathname(self), getTokenLineNumber(self),
              Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
  Ring1_Status_set(Ring1_Status_InvalidSyntactics);
  Ring2_jump();
}

static void
check
  (
    Mkx_Template_ExpressionParser* self,
    void (*error)(Mkx_Template_ExpressionParser*),
    Mkx_Scribe_Hll_TokenType type
  )
{
  if (Ring1_Unlikely(!is(self, type)))
  { (*error)(self); }
}

static void
checkAndNext
  (
    Mkx_Template_ExpressionParser* self,
    void (*error)(Mkx_Template_ExpressionParser*),
    Mkx_Scribe_Hll_TokenType type
  )
{
  check(self, error, type);
  next(self);
}

static Mkx_Scribe_Hll_Node *
parseAdditiveExpression
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Mkx_Scribe_Hll_Node *node = parseMultiplicativeExpression(self);
  while (Mkx_Scribe_Hll_TokenType_Plus == getTokenType(self) || Mkx_Scribe_Hll_TokenType_Minus == getTokenType(self))
  {
    switch (getTokenType(self))
    {
    case Mkx_Scribe_Hll_TokenType_Plus:
    {
      next(self);
      Mkx_Scribe_Hll_Node* operator = Mkx_Scribe_Hll_Node_createPlus(getTokenPosition(self));
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = parseMultiplicativeExpression(self);
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = operator;
    } break;
    case Mkx_Scribe_Hll_TokenType_Minus:
    {
      next(self);
      Mkx_Scribe_Hll_Node* operator = Mkx_Scribe_Hll_Node_createMinus(getTokenPosition(self));
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = parseMultiplicativeExpression(self);
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = operator;
    } break;
    default:
    {
      internalError(self);
    }
    };
  }
  return node;
}

static Mkx_Scribe_Hll_Node *
parseMultiplicativeExpression
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Mkx_Scribe_Hll_Node* node = parseSimpleExpression(self);
  while (Mkx_Scribe_Hll_TokenType_Star == getTokenType(self) || Mkx_Scribe_Hll_TokenType_Slash == getTokenType(self))
  {
    switch (getTokenType(self))
    {
    case Mkx_Scribe_Hll_TokenType_Star:
    {
      next(self);
      Mkx_Scribe_Hll_Node* operator = Mkx_Scribe_Hll_Node_createStar(getTokenPosition(self));
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = parseSimpleExpression(self);
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = operator;
    } break;
    case Mkx_Scribe_Hll_TokenType_Slash:
    {
      next(self);
      Mkx_Scribe_Hll_Node* operator = Mkx_Scribe_Hll_Node_createSlash(getTokenPosition(self));
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = parseSimpleExpression(self);
      Mkx_Scribe_Hll_Node_append(operator, node);
      node = operator;
    } break;
    default:
    {
      internalError(self);
    }
    };
  }
  return node;
}

static Mkx_Scribe_Hll_Node *
parseSimpleExpression
  (
    Mkx_Template_ExpressionParser* self
  )
{
  switch (getTokenType(self))
  {
  case Mkx_Scribe_Hll_TokenType_Name:
  case Mkx_Scribe_Hll_TokenType_LeftParenthesis:
  {
    Mkx_Scribe_Hll_Node *node = parsePrefixExpression(self);
    return node;
  } break;
  case Mkx_Scribe_Hll_TokenType_Plus:
  {
    next(self);
    Mkx_Scribe_Hll_Node* node = Mkx_Scribe_Hll_Node_createUnaryPlus(getTokenPosition(self));
    Mkx_Scribe_Hll_Node* childNode = parseSimpleExpression(self);
    Mkx_Scribe_Hll_Node_append(node, childNode);
    return node;
  } break;
  case Mkx_Scribe_Hll_TokenType_Minus:
  {
    next(self);
    Mkx_Scribe_Hll_Node* node = Mkx_Scribe_Hll_Node_createUnaryPlus(getTokenPosition(self));
    Mkx_Scribe_Hll_Node* childNode = parseSimpleExpression(self);
    Mkx_Scribe_Hll_Node_append(node, childNode);
    return node;
  } break;
  case Mkx_Scribe_Hll_TokenType_String:
  case Mkx_Scribe_Hll_TokenType_Integer:
  {
    return parseConstantExpression(self);
  } break;
  default:
  {
    Mkx_Scribe_Diagnostics_clear(self->diagnostics);
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_LeftParenthesis));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Plus));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Minus));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Name));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Integer));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_String));
    Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
    Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
    Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  } break;
  };
}

/// <code>'>' (NAME|STRING)</code>.
static Mkx_Scribe_Hll_Node *
parseIncludeExpression
  (
    Mkx_Template_ExpressionParser* self
  )
{
  // `'>'`
  check(self, &internalError, Mkx_Scribe_Hll_TokenType_RightAngleBracket);
  Mkx_Scribe_Hll_Node* includeNode = Mkx_Scribe_Hll_Node_createIncludeExpression(getTokenPosition(self));
  next(self);
  // `STRING`
  if (is(self, Mkx_Scribe_Hll_TokenType_String))
  {
    Mkx_Scribe_Hll_Node* includePathnameNode = Mkx_Scribe_Hll_Node_createStringLiteral(getTokenPosition(self), getTokenText(self));
    next(self);
    Mkx_Scribe_Hll_Node_append(includeNode, includePathnameNode);
    return includeNode;
  }
  // `NAME`
  else if (is(self, Mkx_Scribe_Hll_TokenType_Name))
  {
    Mkx_Scribe_Hll_Node* includePathnameNode = Mkx_Scribe_Hll_Node_createNameLiteral(getTokenPosition(self), getTokenText(self));
    next(self);
    Mkx_Scribe_Hll_Node_append(includeNode, includePathnameNode);
    return includeNode;
  }
  else
  {
    Mkx_Scribe_Diagnostics_clear(self->diagnostics);
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Name));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_String));
    Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
    Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
    Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

static Mkx_Scribe_Hll_Node *
parseArgumentList
  (
    Mkx_Template_ExpressionParser* self
  )
{
  if (is(self, Mkx_Scribe_Hll_TokenType_LeftParenthesis))
  {
    Mkx_Scribe_Hll_Node* node = Mkx_Scribe_Hll_Node_createArgumentList(getTokenPosition(self));
    next(self);
    checkAndNext(self, NULL, Mkx_Scribe_Hll_TokenType_RightParenthesis);
    if (!is(self, Mkx_Scribe_Hll_TokenType_RightParenthesis))
    {
      Mkx_Scribe_Diagnostics_clear(self->diagnostics);
      Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Name));
      Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_LeftParenthesis));
      Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
      Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
      Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
      Ring1_Status_set(Ring1_Status_InvalidSyntactics);
      Ring2_jump();
    }
    return node;
  }
  else
  {
    Mkx_Scribe_Diagnostics_clear(self->diagnostics);
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Name));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_LeftParenthesis));
    Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
    Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
    Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

/// <code>
/// expression := NAME argumentList?
/// </code>
static Mkx_Scribe_Hll_Node *
parsePrefixExpression
  (
    Mkx_Template_ExpressionParser* self
  )
{
  if (is(self, Mkx_Scribe_Hll_TokenType_Name))
  {
    Mkx_Scribe_Position* position = getTokenPosition(self);
    Mkx_Scribe_Hll_Node* node = Mkx_Scribe_Hll_Node_createNameLiteral(position, getTokenText(self));
    next(self);
    if (is(self, Mkx_Scribe_Hll_TokenType_LeftParenthesis))
    {
      Mkx_Scribe_Hll_Node* argumentListNode = parseArgumentList(self);
      Mkx_Scribe_Hll_Node* functionCallNode = Mkx_Scribe_Hll_Node_createProcedureCall(position);
      Mkx_Scribe_Hll_Node_append(functionCallNode, node);
      Mkx_Scribe_Hll_Node_append(functionCallNode, argumentListNode);
      node = functionCallNode;
    }
    return node;
  }
  else if (is(self, Mkx_Scribe_Hll_TokenType_LeftParenthesis))
  {
    next(self);
    Mkx_Scribe_Hll_Node* node = parseAdditiveExpression(self);
    checkAndNext(self, &unclosedParenthesesError, Mkx_Scribe_Hll_TokenType_RightParenthesis);
    return node;
  }
  else
  {
    Mkx_Scribe_Diagnostics_clear(self->diagnostics);
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Name));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_LeftParenthesis));
    Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
    Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
    Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

/// <code>
/// constantExpression := (INTEGER | STRING)
/// </code>
static Mkx_Scribe_Hll_Node *
parseConstantExpression
  (
    Mkx_Template_ExpressionParser* self
  )
{
  // `INTEGER`
  if (is(self, Mkx_Scribe_Hll_TokenType_Integer))
  {
    Mkx_Scribe_Hll_Node* node = Mkx_Scribe_Hll_Node_createIntegerLiteral(getTokenPosition(self), getTokenText(self));
    next(self);
    return node;
  }
  // `STRING`
  else if (is(self, Mkx_Scribe_Hll_TokenType_String))
  {
    Mkx_Scribe_Hll_Node *node = Mkx_Scribe_Hll_Node_createStringLiteral(getTokenPosition(self), getTokenText(self));
    next(self);
    return node;
  }
  else
  {
    Mkx_Scribe_Diagnostics_clear(self->diagnostics);
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_Integer));
    Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_String));
    Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
    Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
    Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

/// <code>
/// expression := (includeExpression | additiveExpression)
/// </code>
static Mkx_Scribe_Hll_Node*
parseExpression
  (
    Mkx_Template_ExpressionParser*self
  )
{
  // includeExpression.
  if (is(self, Mkx_Scribe_Hll_TokenType_RightAngleBracket))
  {
    Mkx_Scribe_Hll_Node* node = parseIncludeExpression(self);
    return node;
  }
  // additiveExpression.
  else
  {
    Mkx_Scribe_Hll_Node* node = parseAdditiveExpression(self);
    return node;
  }
}

/// <code>
/// statement := expression ('=' expression)?
/// </code>
static Mkx_Scribe_Hll_Node *
parseStatement
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Mkx_Scribe_Position* position = getTokenPosition(self);
  Mkx_Scribe_Hll_Node* expressionNode0 = parseExpression(self);
  if (is(self, Mkx_Scribe_Hll_TokenType_Equal))
  {
    Mkx_Scribe_Hll_Node* assignmentStatementNode = Mkx_Scribe_Hll_Node_createAssignmentStatement(position);
    next(self);
    Mkx_Scribe_Hll_Node* expressionNode1 = parseExpression(self);
    Mkx_Scribe_Hll_Node_append(assignmentStatementNode, expressionNode0);
    Mkx_Scribe_Hll_Node_append(assignmentStatementNode, expressionNode1);
    return assignmentStatementNode;
  }
  else
  {
    Mkx_Scribe_Hll_Node* expressionStatementNode = Mkx_Scribe_Hll_Node_createExpressionStatement(position);
    Mkx_Scribe_Hll_Node_append(expressionStatementNode, expressionNode0);
    return expressionStatementNode;
  }
}

/// <code>
/// statements := statement (';' statement)*
///             | epsilon
/// </code>
static Mkx_Scribe_Hll_Node *
parseStatements
  (
    Mkx_Template_ExpressionParser* self
  )
{
  Mkx_Scribe_Hll_Node* statements = Mkx_Scribe_Hll_Node_createStatements(getTokenPosition(self));
  while (!is(self, Mkx_Scribe_Hll_TokenType_RightCurlyBracket))
  {
    Mkx_Scribe_Hll_Node *statement = parseStatement(self);
    Mkx_Scribe_Hll_Node_append(statements, statement);
    if (!is(self, Mkx_Scribe_Hll_TokenType_Semicolon))
    {
      break;
    }
    next(self);
  }
  return statements;
}

static Mkx_Scribe_Hll_Node *
parseExpressionOrStatements
  (
    Mkx_Template_ExpressionParser* self
  )
{
  // startOfInput.
  checkAndNext(self, &internalError, Mkx_Scribe_Hll_TokenType_StartOfInput);
  if (self->withExpression && is(self, Mkx_Scribe_Hll_TokenType_LeftParenthesis))
  {
    next(self);
    Mkx_Scribe_Hll_Node* expressionNode = parseExpression(self);
    // ')'
    check(self, &unclosedExpressionError, Mkx_Scribe_Hll_TokenType_RightParenthesis);
    return expressionNode;
  }
  else if (self->withStatements && is(self, Mkx_Scribe_Hll_TokenType_LeftCurlyBracket))
  {
    next(self);
    Mkx_Scribe_Hll_Node* node = parseStatements(self);
    // '}'.
    check(self, &unclosedExpressionError, Mkx_Scribe_Hll_TokenType_RightCurlyBracket);
    return node;
  }
  else
  {
    Mkx_Scribe_Diagnostics_clear(self->diagnostics);
    if (self->withExpression)
    {
      Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_LeftParenthesis));
    }
    if (self->withStatements)
    {
      Mkx_Scribe_Diagnostics_addExpected(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(Mkx_Scribe_Hll_TokenType_LeftCurlyBracket));
    }
    Mkx_Scribe_Diagnostics_setPosition(self->diagnostics, getTokenPosition(self));
    Mkx_Scribe_Diagnostics_setReceived(self->diagnostics, Mkx_Scribe_Hll_TokenType_toString(getTokenType(self)));
    Ring2_String* message = Mkx_Scribe_Diagnostics_makeMessage(self->diagnostics);
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s"), message);
    Ring1_Status_set(Ring1_Status_InvalidSyntactics);
    Ring2_jump();
  }
}

static Mkx_Scribe_Hll_Node*
run
  (
    Mkx_Template_ExpressionParser* self
  )
{
  return parseExpressionOrStatements(self);
}

static void
Mkx_Template_ExpressionParser_visit
  (
    Ring2_Gc* gc,
    Mkx_Template_ExpressionParser* self
  )
{
  if (self->scanner) {
    Ring2_Gc_visit(gc, self->scanner);
  }
  if (self->diagnostics) {
    Ring2_Gc_visit(gc, self->diagnostics);
  }
}

void
Mkx_Template_ExpressionParser_construct
  (
    Mkx_Template_ExpressionParser* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->scanner = (Mkx_Scribe_Hll_Scanner*)Ring2_Value_getObject(&arguments[0]);
  self->diagnostics = Mkx_Scribe_Diagnostics_create(Ring2_Context_get());
  Machine_setClassType((Machine_Object*)self, Mkx_Template_ExpressionParser_getType());
}

Mkx_Template_ExpressionParser*
Mkx_Template_ExpressionParser_create
  (
    Mkx_Scribe_Hll_Scanner* scanner
  )
{
  Machine_Type* ty = Mkx_Template_ExpressionParser_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,scanner));
  Mkx_Template_ExpressionParser* self = Ring1_cast(Mkx_Template_ExpressionParser*,
                                                   Machine_allocateClassObject(ty,
                                                                               NUMBER_OF_ARGUMENTS,
                                                                               arguments));
  return self;
}

static void
Mkx_Template_ExpressionParser_constructClass
  (
    Mkx_Template_ExpressionParser_Class* self
  )
{
  self->run = (Mkx_Scribe_Hll_Node *(*)(Mkx_Template_ExpressionParser*)) & run;
}

Mkx_Scribe_Hll_Node*
Mkx_Template_ExpressionParser_run
  (
    Mkx_Template_ExpressionParser* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Template_ExpressionParser, run, return, self); }
