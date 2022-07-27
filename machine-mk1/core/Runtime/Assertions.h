/// @file Runtime/Assertions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_ASSERTIONS_H_INCLUDED)
#define MACHINE_RUNTIME_ASSERTIONS_H_INCLUDED

#include "Ring2/_Include.h"
#include "Runtime/LogModule.h"
#include "Ring1/Status.h"

#define MACHINE_ASSERT(e, s)                                                                         \
  if (!(e)) {                                                                                        \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,                                       \
                "assertion `%s` failed\n",                                                           \
                #e);                                                                                 \
    Ring1_Status_set(s);                                                                             \
    Ring2_jump();                                                                                    \
  }

#define MACHINE_ASSERT_NOTNULL(e)                                                                       \
  if (!(e)) {                                                                                           \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,                                          \
                "assertion `%s != NULL' failed\n",                                                      \
                #e);                                                                                    \
    Ring1_Status_set(Ring1_Status_InvalidArgument);                                                     \
    Ring2_jump();                                                                                       \
  }

#define MACHINE_ASSERT_UNREACHABLE()                                                               \
  Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,                                       \
              "unreachable program point reached\n");                                              \
  Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);                                   \
  Ring2_jump();

#endif // MACHINE_RUNTIME_ASSERTIONS_H_INCLUDED
