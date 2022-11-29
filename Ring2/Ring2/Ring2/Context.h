// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Context.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_CONTEXT_H_INCLUDED)
#define RING2_CONTEXT_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Context.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


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
