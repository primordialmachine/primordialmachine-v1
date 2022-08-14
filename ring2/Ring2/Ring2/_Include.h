// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2__INCLUDE_H_INCLUDED)
#define RING2__INCLUDE_H_INCLUDED

#define RING2_INTERNAL (1)
#include "Ring2/Assert.h"
#include "Ring2/Gc.h"
#include "Ring2/Types.h"
#include "Ring2/Context.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Log.h"
#include "Ring2/Operations.h"
#include "Ring2/TypeSystem/ClassType.h"
#include "Ring2/TypeSystem/EnumerationType.h"
#include "Ring2/TypeSystem/InterfaceType.h"
#include "Ring2/Types/Value.h"
#include "Ring2/Old/Value.h"
#undef RING2_INTERNAL

#endif // RING2__INCLUDE_H_INCLUDED
