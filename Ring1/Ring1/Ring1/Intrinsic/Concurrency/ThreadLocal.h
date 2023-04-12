// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/ThreadLocal.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRRINSIC_CONCURRENCY_THREADLOCAL_H_INCLUDED)
#define RING1_INTRRINSIC_CONCURRENCY_THREADLOCAL_H_INCLUDED

#if defined(_MSC_VER)
  #define Ring1_Intrinsic_ThreadLocal() __declspec(thread)
#else
  #error("Ring1_Intrinsic_ThreadLocal() not supported for this environment")
#endif

#endif // RING1_INTRRINSIC_CONCURRENCY_THREADLOCAL_H_INCLUDED