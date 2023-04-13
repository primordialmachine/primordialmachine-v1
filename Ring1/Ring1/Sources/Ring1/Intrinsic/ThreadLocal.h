// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/ThreadLocal.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_THREADLOCAL_H_INCLUDED)
#define RING1_INTRINSIC_THREADLOCAL_H_INCLUDED

// https://documentation.primordialmachine.com/api/ring1-library/intrinsic-library/Ring1_ThreadLocal
#if defined(_MSC_VER)
  #define Ring1_ThreadLocal() __declspec(thread)
#else
  #error("environment not supported")
#endif

#endif // RING1_INTRINSIC_THREADLOCAL_H_INCLUDED
