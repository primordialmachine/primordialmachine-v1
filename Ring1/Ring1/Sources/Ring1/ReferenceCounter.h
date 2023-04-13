// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/ReferenceCounter.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_REFERENCECOUNTER_H_INCLUDED)
#define RING1_REFERENCECOUNTER_H_INCLUDED


#include <inttypes.h>


/// @brief The opaque type of a reference counter.
typedef volatile int32_t Ring1_ReferenceCounter;


/// @brief Atomically read a reference counter.
/// @param referenceCounter A pointer to the reference counter.
/// @return The value of the reference counter.
int32_t
Ring1_ReferenceCounter_get
  (
    Ring1_ReferenceCounter const* referenceCounter
  );

/// @brief Atomically increment a reference counter.
/// @param referenceCounter A pointer to the reference counter.
/// @return The new value of the reference counter.
int32_t
Ring1_ReferenceCounter_increment
  (
    Ring1_ReferenceCounter* referenceCounter
  );

/// @brief Atomically decrement a reference counter.
/// @param referenceCouner A pointer to the reference counter.
/// @return The new value of the reference counter.
int32_t
Ring1_ReferenceCounter_decrement
  (
    Ring1_ReferenceCounter* referenceCounter
  );


#endif // RING1_REFERENCECOUNTER_H_INCLUDED
