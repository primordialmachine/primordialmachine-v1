/// @file Runtime/ArrayUtilities.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#if !defined(MACHINE_RUNTIME_ARRAYUTILITIES_H_INCLUDED)
#define MACHINE_RUNTIME_ARRAYUTILITIES_H_INCLUDED

#include "Ring2/_Include.h"

/// @brief
/// Create a copy of the old array.
/// @param sizeNew
/// The size of the new array.
/// @param arrayOld
/// The old array.
/// @param sizeold
/// The size of the old array.
/// @param deallocate
/// If @a true the old array is deallocated if this function succeeds.
/// @return
/// The new array.
/// @remark
/// The first min(sizeNew,sizeOld) elements of the old and the new array are equal.
/// Furthermore, if sizeNew > sizeOld the elements in the new array at the indices [sizeOld, sizeNew - 1] are assigned the <code>Void</code> value.
Machine_Value* Machine_ArrayUtilities_copyOf(size_t sizeNew, Machine_Value* arrayOld, size_t sizeOld, bool deallocate);

#endif // MACHINE_RUNTIME_ARRAYUTILITIES_H_INCLUDED
