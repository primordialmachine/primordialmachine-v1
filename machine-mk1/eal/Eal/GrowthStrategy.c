/// @file Eal/isPowerOfTwo.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_EAL_PRIVATE (1)
#include "Eal/GrowthStrategy.h"


#include "Eal/leastPowerOfTwoGreaterThanOrEqualTo.h"



int Machine_Eal_getBestCapacity(size_t oldCapacity, size_t requiredAdditionalCapacity, size_t maximalCapacity, size_t* newCapacity) {
  if (oldCapacity > maximalCapacity) {
    // unable to satisfy this request.
    return MACHINE_EAL_GROWTHSTRATEGY_INVALIDARGUMENT;
  }
  if (requiredAdditionalCapacity == 0) {
    // new capacity is old capacity.
    *newCapacity = oldCapacity;
    return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS;
  }
  if (requiredAdditionalCapacity > maximalCapacity) {
    // unable to satisfy this request.
    return MACHINE_EAL_GROWTHSTRATEGY_POSITIVEOVERFLOW;
  }

  const size_t oldCapacity2 = oldCapacity / 2;

  // The new capacity is the old capacity plus the required additional capacity.
  // If this addition overflows, then return with failure.
  if (oldCapacity > maximalCapacity - requiredAdditionalCapacity) {
    // unable to satisfy this request.
    return MACHINE_EAL_GROWTHSTRATEGY_POSITIVEOVERFLOW;
  }
  *newCapacity = oldCapacity + requiredAdditionalCapacity;

  // We can fulfil this request.

  // Optimize #1
  // Set the optimized new capacity to a value that
  // - is the least power of two greater than or equal to the "old" new capacity and
  // - is smaller than or equal to the maximal capacity.
  // If such a value exists, return the optimized new capacity.
  size_t temporary;
  if (Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_sz(&temporary, *newCapacity)) {
    if (temporary <= maximalCapacity) {
      *newCapacity = temporary;
      return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS;
    }
  }
  // Optimize #2
  // Set the optimized new capacity to a value that
  // - is equal to 1.5 * old capacity and
  // - is smaller than or equal to the maximal capacity.
  // If such a value exists, return the optimized new capacity.
  if (requiredAdditionalCapacity < oldCapacity2 && oldCapacity <= maximalCapacity - oldCapacity2) {
    *newCapacity = oldCapacity + oldCapacity2;
    return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS;
  }

  // Return the optimized new capacity.
  return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS;
}