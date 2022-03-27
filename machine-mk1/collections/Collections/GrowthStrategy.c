/// @file Collections/GrowthStrategy.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/GrowthStrategy.h"

#include "Ring1/Memory/recomputeSize.h"
#include "Ring1/Status.h"

Machine_StatusValue Machine_Collections_getBestCapacity(size_t oldCapacity,
                                                        size_t requiredAdditionalCapacity,
                                                        size_t maximalCapacity,
                                                        size_t* newCapacity) {


    if (Ring1_Memory_recomputeSize_sz(0, maximalCapacity, oldCapacity, requiredAdditionalCapacity,
                                      newCapacity, true)) {
      switch (Ring1_Status_get()) {
        case Ring1_Status_InvalidArgument:
          return Machine_Status_InvalidArgument;
        case Ring1_Status_NotExists:
          return Machine_Status_CapacityExhausted;
        default:
          return Machine_Status_EnvironmentFailed;
      };
    };
    return Machine_Status_Success;
}
