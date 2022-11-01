// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Types.h"
#undef RING2_PRIVATE


#include "Ring1/Conversion.h"


Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Conversion)
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  Ring1_Dependency(Ring2, ArrayModule)
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  Ring1_Dependency(Ring2, StringModule)
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  Ring1_Dependency(Ring2, ObjectModule)
#endif
Ring1_EndDependencies()

Ring1_CheckReturn() Ring1_Result
Ring2_Types_startup
  (
  )
{ return startupDependencies(); }

void
Ring2_Types_shutdown
  (
  )
{ shutdownDependencies(); }

Ring1_Module_Define(Ring2, TypesModule, Ring2_Types_startup, Ring2_Types_shutdown)