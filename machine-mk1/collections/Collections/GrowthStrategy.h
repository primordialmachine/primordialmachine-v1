/// @file Collections/GrowthStrategy.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_GROWTHSTRATEGY_H_INCLUDEd)
#define MACHINE_COLLECTIONS_GROWTHSTRATEGY_H_INCLUDEd

#include "Collections/_header.i"

/// @brief Compute a "best" new capacity based on an old capacity, a required additional capacity,
/// and a maximal capacity.
/// @param oldCapacity The old capacity.
/// @param requiredAdditionalCapacity The required additional capacity.
/// @param maximalCapacity The maximal capacity.
/// @param newCapacity A pointer to a size_t variable receiving the "best" new capacity.
/// @return Machine_Status_InvalidArgument if oldCapacity > maximalCapacity.
/// @return Machine_Status_PositiveOverflow if requiredAdditionalCapacity > maximalCapacity
/// @remark
/// This growth strategy computes the new size as follows:
/// - Let newCapacity' = oldCapacity + requiredAdditionalCapacity if that expression does not
/// overflow.
///   Otherwise return Machine_Status_PositiveOverflow.
/// - Let v be the least power of two greater than or equal to newCapacity' and smaller than or
/// equal to maximalCapacity.
///   Let newCapacity'' = v and return Machine_Status_Success if v exists.
///   Otherwise continue.
/// - If requiredNewCapacity < oldCapacity / 2:
///     Let w be 1.5 * oldCapacity smaller than or equal to maximalCapacity.
///     Let newCapacity'' = w and return Machine_Status_Success if w exists.
///     Otherwise continue.
/// - Return Machine_Status_Success.
Machine_StatusValue Machine_Collections_getBestCapacity(size_t oldCapacity,
                                                        size_t requiredAdditionalCapacity,
                                                        size_t maximalCapacity,
                                                        size_t* newCapacity);

#endif // MACHINE_COLLECTIONS_GROWTHSTRATEGY_H_INCLUDEd
