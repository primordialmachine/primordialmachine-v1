// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2__INCLUDE_H_INCLUDED)
#define RING2__INCLUDE_H_INCLUDED

#define RING2_PRIVATE (1)
#include "Ring2/Assert.h"
#include "Ring2/Context.h"
#include "Ring2/Instructions.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Log.h"
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/StaticVariables.h"
#include "Ring2/Test/Test.h"
#include "Ring2/Test/Tests.h"
#include "Ring2/TypeSystem/ClassType.h"
#include "Ring2/TypeSystem/EnumerationType.h"
#include "Ring2/TypeSystem/InterfaceType.h"
#undef RING2_PRIVATE

#endif // RING2__INCLUDE_H_INCLUDED
