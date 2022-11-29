// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Status.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Status.h"

#include "Ring1/Intrinsic/ThreadLocal.h"

Ring1_ThreadLocal() static Ring1_Status g_status = Ring1_Status_Success;

Ring1_CheckReturn() Ring1_Status
Ring1_Status_get
  (
  )
{ return g_status; }

void
Ring1_Status_set
  (
    Ring1_Status status
  )
{ g_status = status; }
