// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Assert.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_ASSERT_H_INCLUDED)
#define RING2_ASSERT_H_INCLUD

#include "Ring2/Log.h"
#include "Ring2/JumpTarget.h"
#include "Ring1/Status.h"

#define Ring2_assert(e, s)                                                                           \
  if (!(e)) {                                                                                        \
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,                                           \
              "assertion `%s` failed\n",                                                             \
              #e);                                                                                   \
    Ring1_Status_set(s);                                                                             \
    Ring2_jump();                                                                                    \
  }

#define Ring2_assertNotNull(e)                                                                       \
  if (!(e)) {                                                                                        \
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,                                           \
              "assertion `%s != NULL' failed\n",                                                     \
              #e);                                                                                   \
    Ring1_Status_set(Ring1_Status_InvalidArgument);                                                  \
    Ring2_jump();                                                                                    \
  }

#define Ring2_unreachable()                                                                          \
  Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,                                             \
            "unreachable program point reached\n");                                                  \
  Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);                                     \
  Ring2_jump();


#endif // RING2_ASSERT_H_INCLUDED
