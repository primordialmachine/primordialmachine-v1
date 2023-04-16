// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/NodeType.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Hll/NodeType.h"


MACHINE_DEFINE_ENUMERATIONTYPE(Mkx_Scribe_Hll_NodeKind);

Ring2_String*
Mkx_Scribe_Hll_NodeKind_toString
  (
    Mkx_Scribe_Hll_NodeKind self
  )
{
  switch (self)
  {
#define Define(X, Y) \
    case Mkx_Scribe_Hll_NodeType_##X: { \
      return Ring2_String_fromC(false, Y); \
    } break;
#include "Mkx/Scribe/Hll/NodeType.i"
#undef Define
  default:
    Ring2_emitf(Ring2_Context_get(),
                Ring2_String_fromC(false, "%s:%i: unhandled enumeration element\n"),
                Ring2_String_fromC(false, __FILE__),
                __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}