// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Context.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_CONTEXT_H_INCLUDED)
#define RING2_CONTEXT_H_INCLUDED

#include "Ring2/Configuration.h"
#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

typedef struct Ring2_Context Ring2_Context;

Ring1_CheckReturn() Ring2_Context*
Ring2_Context_get
  (
  );

Ring1_CheckReturn() Ring1_Result
Ring2_Context_startup
  (
  );

void
Ring2_Context_shutdown
  (
  );

#endif // RING2_CONTEXT_H_INCLUDED
