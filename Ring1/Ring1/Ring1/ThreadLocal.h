// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/Concurrency/ThreadLocal.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_INTRRINSIC_CONCURRENCY_THREADLOCAL_H_INCLUDED)
#define MKX_INTRRINSIC_CONCURRENCY_THREADLOCAL_H_INCLUDED

#if defined(_MSC_VER)
  #define Mkx_Intrinsic_ThreadLocal() __declspec(thread)
#else
  #error("Mkx_Intrinsic_ThreadLocal() not supported for this environment")
#endif

#endif // MKX_INTRRINSIC_CONCURRENCY_THREADLOCAL_H_INCLUDED