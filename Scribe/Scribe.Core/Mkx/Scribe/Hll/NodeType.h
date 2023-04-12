// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/NodeType.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_HLL_NODETYPE_H_INCLUDED)
#define MKX_SCRIBE_HLL_NODETYPE_H_INCLUDED


#include "Mkx/Scribe/Common.h"


MACHINE_DECLARE_ENUMERATIONTYPE(Mkx_Scribe_Hll_NodeKind)

enum Mkx_Scribe_Hll_NodeKind {
#define Define(NAME, DESCRIPTION) \
  Mkx_Scribe_Hll_NodeType_##NAME,
#include "Mkx/Scribe/Hll/NodeType.i"
#undef Define
};

Ring2_String*
Mkx_Scribe_Hll_NodeKind_toString
  (
    Mkx_Scribe_Hll_NodeKind self
  );

#endif // MKX_SCRIBE_HLL_NODETYPE_H_INCLUDED
