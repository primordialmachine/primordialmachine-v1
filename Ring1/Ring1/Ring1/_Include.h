// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1__INCLUDE_H_INCLUDED)
#define RING1__INCLUDE_H_INCLUDED

#include "Ring1/Atom/_Include.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Collections/_Include.h"
#include "Ring1/FileSystem/_Include.h"
#include "Ring1/Intrinsic/_Include.h"
#include "Ring1/TypeName/_Include.h"
#include "Ring1/Memory.h"
#include "Ring1/Module.h"

Ring1_CheckReturn() Ring1_Result
Ring1_startup
  (
  );

void
Ring1_shutdown
  (
  );

#endif // RING1__INCLUDE_H_INCLUDED
