// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Annotations/NonNull.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_NONNULL_H_INCLUDED)
#define RING1_INTRINSIC_NONNULL_H_INCLUDED

/// @brief Function annotation indicating that pointer arguments must not be null.
/// @param ... List of argument one-based parameter indices.
/// The index i indicates the parameter must not be null if it is a pointer type.
/// If this list is empty, all pointer arguments must be non-null.
/// @remark Example usage
/// @code
/// Ring1_NonNull(1,3) void f(void *x, void *y, void *z)
/// @endcode
/// Indicates that x and z must not be null.
/// @code
/// Ring1_NonNull() void f(void *x, void *y, void *z)
/// @endcode
/// Indicates that x, y, and z must be non null.
#if defined(__GNUC__)
  #define Ring1_NonNull(...) __attribute((nonnull(__VA_ARGS__)))
#elif defined(_MSC_VER)
  #define Ring1_NonNull(...)
#else
  #error("unsupported compiler")
#endif

#endif // RING1_INTRINSIC_NONNULL_H_INCLUDED
