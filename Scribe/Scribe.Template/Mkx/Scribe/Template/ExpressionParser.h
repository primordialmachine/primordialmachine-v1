#if !defined(MKX_SCRIBE_EXPRESSIONPARSER_H_INCLUDED)
#define MKX_SCRIBE_EXPRESSIONPARSER_H_INCLUDED


#include "Mkx/Scribe/Hll.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Template_ExpressionParser)

struct Mkx_Template_ExpressionParser_Class {
  Machine_Object_Class _parent;
  Mkx_Scribe_Hll_Node* (*run)(Mkx_Template_ExpressionParser * self);
};

struct Mkx_Template_ExpressionParser {
  Machine_Object _parent;
  Mkx_Scribe_Hll_Scanner* scanner;
  Mkx_Scribe_Diagnostics* diagnostics;
  bool withExpression;
  bool withStatements;
};

void
Mkx_Template_ExpressionParser_construct
  (
    Mkx_Template_ExpressionParser* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Mkx_Template_ExpressionParser*
Mkx_Template_ExpressionParser_create
  (
    Mkx_Scribe_Hll_Scanner* scanner
  );

Mkx_Scribe_Hll_Node*
Mkx_Template_ExpressionParser_run
  (
    Mkx_Template_ExpressionParser* self
  );

#endif // MKX_SCRIBE_EXPRESSIONPARSER_H_INCLUDED
