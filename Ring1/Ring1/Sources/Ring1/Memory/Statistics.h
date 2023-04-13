// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/Statistics.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_MEMORY_STATISTICS_H_INCLUDED)
#define RING1_MEMORY_STATISTICS_H_INCLUDED

#include "Ring1/Memory/Configuration.h"

#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS

#include <stdint.h> // Keep it minimal.

/// @todo Should be internal.
/// IMPORTANT:
/// The tag is allocated in front of the memory block. The payload address is the
/// address after the tag.
/// For Visual C++ we require (among other things for the reason when functions with
/// alignment requirements are used on the memory block e.g. Ring1.ReferenceCounter)
/// that this address is a multiple of 64 Bit/8 Byte.
/// We hence must ensure that Ring1_Memory_Statistics_Tag has a size which is a multiple
/// of 64 Bit/8 Byte.
/// The static assertion below fails if the size of Ring1_Memory_Statistics_Tag is not
/// a multiple of 64 Bit/8 Byte.
typedef struct Ring1_Memory_Statistics_Tag {
  size_t n;
#if defined(_MSC_VER) && !defined(WIN64)
  // Ensure that the size of this struct is a multiple of 64 Bit/8 Byte.
  char padding[2];
#endif
} Ring1_Memory_Statistics_Tag;

static_assert(sizeof(Ring1_Memory_Statistics_Tag) % 8 == 0, "not a multiple 64 Bit/8 Byte");


typedef struct Ring1_Memory_Statistics {
  size_t currentMetadata; ///< @brief Number of metadata bytes.
  size_t currentData;     ///< @brief Number of data Bytes.
  size_t maximumMetadata; ///< @brief All time high number of metadata bytes.
  size_t maximumData;     ///< @brief All time high number of data bytes.
} Ring1_Memory_Statistics;

#define Ring1_Memory_Statistics_initializeStatic() { .currentMetadata = 0, .currentData = 0, .maximumMetadata = 0, .maximumData = 0 }

inline void
Ring1_Memory_Statistics_initialize
  (
    Ring1_Memory_Statistics* statistics
  )
{
  statistics->currentData = 0;
  statistics->currentMetadata = 0;
  statistics->maximumData = 0;
  statistics->maximumMetadata = 0;
}

inline void
Ring1_Memory_Statistics_uninitialize
  (
    Ring1_Memory_Statistics* statistics
  )
{}

inline double
Ring1_Memory_Statistics_getMaximumRatio
  (
    const Ring1_Memory_Statistics* statistics
  )
{
  if (statistics->maximumData == 0) return 0.0;
  return (double)statistics->maximumMetadata / (double)statistics->maximumData;
}

inline double
Ring1_Memory_Statistics_getCurrentRatio
  (
    const Ring1_Memory_Statistics* statistics
  )
{
  if (statistics->currentData == 0) return 0.0;
  return (double)statistics->currentMetadata / (double)statistics->currentData;
}

inline size_t
Ring1_minimum_size
  (
    size_t x,
    size_t y
  )
{
  return x < y ? x : y;
}

inline size_t
Ring1_maximum_size
  (
    size_t x,
    size_t y
  )
{
  return x > y ? x : y;
}

inline void
Ring1_Memory_Statistics_allocated
  (
    Ring1_Memory_Statistics *statistics,
    size_t data,
    size_t metadata
  )
{
 statistics->currentData += data;
 statistics->currentMetadata += metadata;

 statistics->maximumData = Ring1_maximum_size(statistics->maximumData,statistics->currentData);
 statistics->maximumMetadata = Ring1_maximum_size(statistics->maximumMetadata,statistics->currentMetadata);
}

inline void
Ring1_Memory_Statistics_deallocated
  (
    Ring1_Memory_Statistics *statistics,
    size_t data,
    size_t metadata
  )
{
 statistics->currentData -= data;
 statistics->currentMetadata -= metadata;

 statistics->maximumData = Ring1_maximum_size(statistics->maximumData,statistics->currentData);
 statistics->maximumMetadata = Ring1_maximum_size(statistics->maximumMetadata,statistics->currentMetadata);
}

inline void
Ring1_Memory_Statistics_reallocated
  (
    Ring1_Memory_Statistics *statistics,
    size_t oldData,
    size_t newData,
    size_t oldMetadata,
    size_t newMetadata
  )
{
 statistics->currentData -= oldData;
 statistics->currentData += newData;

 statistics->currentMetadata -= oldMetadata;
 statistics->currentMetadata += newMetadata;

 statistics->maximumData = Ring1_maximum_size(statistics->maximumData,statistics->currentData);
 statistics->maximumMetadata = Ring1_maximum_size(statistics->maximumMetadata,statistics->currentMetadata);
}

void
Ring1_Memory_Statistics_dump
  (
    const Ring1_Memory_Statistics* statistics
  );

#endif // RING1_MEMORY_WITH_STATISTICS

#endif // RING1_MEMORY_STATISTICS_H_INCLUDED
