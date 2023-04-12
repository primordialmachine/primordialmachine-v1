// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/parseTemplate.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/parseTemplate.h"


#include "Mkx/Scribe/Hll.h"
#include "Mkx/Scribe/Template/TemplateScanner.h"
#include "Mkx/Scribe/Template/parseExpression.h"
#include "Mkx/Scribe/Common.h"

#include "Mkx/Scribe/Template/TemplateParser.h"

#define TYPE Mkx_Template_TemplateParser
#define PARENT(expression) ((Mkx_Scribe_Node *)(expression))
#include "Mkx/Scribe/Hll/Parselets.Core.i"
#undef PARENT
#undef TYPE

static Mkx_Scribe_Hll_Node*
toLoadStringNode
  (
    Mkx_Scribe_Position* position,
    Ring2_String* text
  )
{ return Mkx_Scribe_Hll_Node_createStringLiteral(position, text); }

Mkx_Scribe_Hll_Node*
Mkx_Template_parseTemplate
  (
    Mkx_SymbolScanner *symbolScanner
  )
{
  Mkx_Template_TemplateScanner* templateScanner = Mkx_Template_TemplateScanner_create(symbolScanner);
  Mkx_Template_TemplateParser *templateParser = Mkx_Template_TemplateParser_create(templateScanner);
  Mkx_Scribe_Hll_Node* templateNode =  Mkx_Scribe_Hll_Node_createTemplate(getTokenPosition(templateParser));
  while (getTokenType(templateParser) != Mkx_Scribe_Hll_TokenType_EndOfInput)
  {
    switch (getTokenType(templateParser))
    {
    case Mkx_Scribe_Hll_TokenType_StartOfInput:
    {
      next(templateParser);
    } break;
    case Mkx_Scribe_Hll_TokenType_String:
    {
      Mkx_Scribe_Hll_Node* node = toLoadStringNode(getTokenPosition(templateParser), getTokenText(templateParser));
      Mkx_Scribe_Hll_Node_append(templateNode, node);
      next(templateParser);
    } break;
    case Mkx_Scribe_Hll_TokenType_ExpressionOpeningDelimiter:
    case Mkx_Scribe_Hll_TokenType_StatementOpeningDelimiter:
    {
      Mkx_Scribe_Hll_Node* node = Mkx_Template_parseExpression(symbolScanner);
      next(templateParser);
      Mkx_Scribe_Hll_Node_append(templateNode, node);
    } break;
    default:
    {
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s:%i: malformed opening delimiter: expected '{'\n"),
                  getTokenPathname(templateParser), getTokenLineNumber(templateParser));
      Ring1_Status_set(Ring1_Status_InvalidSyntactics);
      Ring2_jump();
    }
    };
  }
  return templateNode;
}
