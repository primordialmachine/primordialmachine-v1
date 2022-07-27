// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/SweepStatistics.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_GC_SWEEPSTATISTICS_H_INCLUDED)
#define RING2_GC_SWEEPSTATISTICS_H_INCLUDED

#include <inttypes.h>

/// Type of a statistics for
/// - a sweep phase of a single arena or
/// - sweep phases of multiple arenas.
typedef struct Ring2_Gc_SweepStatistics
{

  /// @brief The number of dead objects.
  int64_t dead;

  /// @brief The number of live objects.
  int64_t live;

} Ring2_Gc_SweepStatistics;

#endif // RING2_GC_SWEEPSTATISTICS_H_INCLUDED
