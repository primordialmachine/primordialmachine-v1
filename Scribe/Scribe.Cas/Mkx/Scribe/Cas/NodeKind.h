// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/NodeKind.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#pragma once

#include "Mkx/Scribe/Common.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Mkx_Scribe_Cas_NodeKind);

enum Mkx_Scribe_Cas_NodeKind
{
#define Define(NAME) \
  Mkx_Scribe_Cas_NodeKind_##NAME,

#include "Mkx/Scribe/Cas/NodeKind.i"

#undef Define
};
