// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/RunStatistics.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_GC_RUNSTATISTICS_H_INCLUDED)
#define RING2_GC_RUNSTATISTICS_H_INCLUDED

#include "Ring2/Gc/SweepStatistics.h"

/// Type of a statistics for a run.
typedef struct Ring2_Gc_RunStatistics
{
  Ring2_Gc_SweepStatistics sweep;
} Ring2_Gc_RunStatistics;

#endif // RING2_GC_RUNSTATISTICS_H_INCLUDED
