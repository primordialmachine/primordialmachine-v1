/// @file Atf/Assertions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_ATF_ASSERTIONS_H_INCLUDED)
#define MACHINE_ATF_ASSERTIONS_H_INCLUDED



#include "_Runtime.h"



#define MACHINE_ATF_ASSERT(e) \
  if (!(e)) { \
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "test assertion `%s` failed\n", #e); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  }



#endif // MACHINE_ATF_ASSERTIONS_H_INCLUDED
