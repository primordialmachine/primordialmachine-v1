// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Template/parseExpression.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Template/parseExpression.h"


#include "Mkx/Scribe/Template/ExpressionScanner.h"
#include "Mkx/Scribe/Template/ExpressionParser.h"


Mkx_Scribe_Hll_Node*
Mkx_Template_parseExpression
  (
    Mkx_SymbolScanner *symbolScanner
  )
{
  Mkx_Template_ExpressionParser *parser = Mkx_Template_ExpressionParser_create(Ring1_cast(Mkx_Scribe_Hll_Scanner*, Mkx_Template_ExpressionScanner_create(symbolScanner)));
  parser->withExpression = true;
  parser->withStatements = true;
  // Parse the node.
  Mkx_Scribe_Hll_Node* node = Mkx_Template_ExpressionParser_run(parser);
  // Return the node.
  return node;
}
