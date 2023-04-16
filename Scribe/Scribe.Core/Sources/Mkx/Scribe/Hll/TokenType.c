#include "Mkx/Scribe/Hll/TokenType.h"

MACHINE_DEFINE_ENUMERATIONTYPE(Mkx_Scribe_Hll_TokenType);

Ring2_String*
Mkx_Scribe_Hll_TokenType_toString
  (
    Mkx_Scribe_Hll_TokenType self
  )
{
  switch (self)
  {
#define Define(X, Y) \
    case Mkx_Scribe_Hll_TokenType_##X: { \
      return Ring2_String_fromC(false, Y); \
    } break;
#include "Mkx/Scribe/Hll/TokenType.i"
#undef Define
  default: {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s:%i: unhandled enumeration element\n"),
                Ring2_String_fromC(false, __FILE__), __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  };
  };
}
