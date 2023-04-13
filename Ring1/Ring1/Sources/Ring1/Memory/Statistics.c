// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/Statistics.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Memory/Statistics.h"

#include <math.h>
#include <stdio.h>

#if defined(RING1_MEMORY_WITH_STATISTICS) && 1 == RING1_MEMORY_WITH_STATISTICS
void
Ring1_Memory_Statistics_dump
  (
    const Ring1_Memory_Statistics* statistics
  )
{
  size_t kilobyte, byte;
  double ratio;

  // maximum
  byte = statistics->maximumData;
  kilobyte = byte / 1000;
  byte %= 1000;
  fprintf(stdout, "maximum: %zu Kilobyte, %zu Byte\n", kilobyte, byte);

  byte = statistics->maximumMetadata;
  kilobyte = byte / 1000;
  byte %= 1000;
  fprintf(stdout, "maximum overhead: %zu Kilobyte, %zu Byte\n", kilobyte, byte);

  ratio = Ring1_Memory_Statistics_getMaximumRatio(statistics) * 100.0;
  ratio = round(ratio * 100.0) / 100.0;
  fprintf(stdout, "maximum ratio: %.2f%%\n", ratio);

  // current
  byte = statistics->currentData;
  kilobyte = byte / 1000;
  byte %= 1000;
  fprintf(stdout, "current: %zu Kilobyte, %zu Byte\n", kilobyte, byte);

  byte = statistics->currentMetadata;
  kilobyte = byte / 1000;
  byte %= 1000;
  fprintf(stdout, "current overhead: %zu Kilobyte, %zu Byte\n", kilobyte, byte);

  ratio = Ring1_Memory_Statistics_getCurrentRatio(statistics) * 100.0;
  ratio = round(ratio * 100.0) / 100.0;
  fprintf(stdout, "current ratio: %.2f%%\n", ratio);
}
#endif
