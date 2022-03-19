/// @file Runtime/ArrayUtilities.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/ArrayUtilities.h"

#include "_Runtime.h"

Machine_Value* Machine_ArrayUtilities_copyOf(size_t sizeNew, Machine_Value* arrayOld,
                                             size_t sizeOld, bool deallocate) {
  if (deallocate) {
    Machine_Value* arrayNew
        = Machine_Eal_Memory_reallocateArray(arrayOld, sizeof(Machine_Value), sizeNew);
    if (!arrayNew) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    for (size_t i = sizeOld, n = sizeNew; i < n; ++i) {
      Machine_Value_setVoid(&(arrayNew[i]), Machine_Void_Void);
    }
    return arrayNew;
  } else {
    Machine_Value* arrayNew = Machine_Eal_Memory_allocateArray(sizeof(Machine_Value), sizeNew);
    if (!arrayNew) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    for (size_t i = 0, n = sizeOld; i < n; ++i) {
      arrayNew[i] = arrayNew[i];
    }
    for (size_t i = sizeOld, n = sizeNew; i < n; ++i) {
      Machine_Value_setVoid(&(arrayNew[i]), Machine_Void_Void);
    }
    return arrayNew;
  }
}
