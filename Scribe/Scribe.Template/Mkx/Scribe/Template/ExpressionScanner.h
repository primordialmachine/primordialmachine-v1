#if !defined(MKX_SCRIBE_TEMPLATE_EXPRESSIONSCANNER_H_INCLUDED)
#define MKX_SCRIBE_TEMPLATE_EXPRESSIONSCANNER_H_INCLUDED


#include "Mkx/Scribe/Hll.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Template_ExpressionScanner)

struct Mkx_Template_ExpressionScanner_Class {
  Mkx_Scribe_Hll_Scanner_Class _parent;
};

struct Mkx_Template_ExpressionScanner {
  Mkx_Scribe_Hll_Scanner _parent;
};

void
Mkx_Template_ExpressionScanner_construct
  (
    Mkx_Template_ExpressionScanner* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Mkx_Template_ExpressionScanner *
Mkx_Template_ExpressionScanner_create
    (
      Mkx_SymbolScanner* symbolScanner
    );

#endif // MKX_SCRIBE_TEMPLATE_EXPRESSIONSCANNER_H_INCLUDED
