/// @file Collections/GrowthStrategy.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/GrowthStrategy.h"

Machine_StatusValue Machine_Collections_getBestCapacity(size_t oldCapacity,
                                                        size_t requiredAdditionalCapacity,
                                                        size_t maximalCapacity,
                                                        size_t* newCapacity) {
  int status = Machine_Eal_getBestCapacity(oldCapacity, requiredAdditionalCapacity, maximalCapacity,
                                           newCapacity);
  switch (status) {
    case MACHINE_EAL_GROWTHSTRATEGY_INVALIDARGUMENT:
      return Machine_Status_InvalidArgument;
    case MACHINE_EAL_GROWTHSTRATEGY_POSITIVEOVERFLOW:
      return Machine_Status_PositiveOverflow;
    case MACHINE_EAL_GROWTHSTRATEGY_SUCCESS:
      return Machine_Status_Success;
    default:
      return Machine_Status_EnvironmentFailed;
  };
}
