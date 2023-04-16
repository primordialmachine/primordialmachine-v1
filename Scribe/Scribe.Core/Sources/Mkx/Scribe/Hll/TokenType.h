#if !defined(MKX_SCRIBE_HLL_TOKENTYPE_H_INCLUDED)
#define MKX_SCRIBE_HLL_TOKENTYPE_H_INCLUDED


#include "Mkx/Scribe/Common.h"


MACHINE_DECLARE_ENUMERATIONTYPE(Mkx_Scribe_Hll_TokenType)

enum Mkx_Scribe_Hll_TokenType
{
#define Define(X, Y) \
  Mkx_Scribe_Hll_TokenType_##X,
#include "Mkx/Scribe/Hll/TokenType.i"
#undef Define
};

Ring2_String*
Mkx_Scribe_Hll_TokenType_toString
  (
    Mkx_Scribe_Hll_TokenType self
  );

#endif // MKX_SCRIBE_HLL_TOKENTYPE_H_INCLUDED
