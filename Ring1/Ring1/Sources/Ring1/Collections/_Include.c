// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/_Include.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_COLLECTIONS_PRIVATE (1)
#include "Ring1/Collections/_Include.h"
#undef RING1_COLLECTIONS_PRIVATE


#include "Ring1/Memory/_Include.h"


static Ring1_Result
initializeDependencies
  (
  );

static void
uninitializeDependencies
  (
  );

Ring1_Module_Define(Ring1, Collections, initializeDependencies, uninitializeDependencies)

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, PointerDeque)
  Ring1_Dependency(Ring1, PointerHashMap)
  Ring1_Dependency(Ring1, PointerList)
Ring1_EndDependencies()

static Ring1_Result
initializeDependencies
  (
  )
{ return startupDependencies(); }

static void
uninitializeDependencies
  (
  )
{ shutdownDependencies(); }
