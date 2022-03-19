#if !defined(MACHINE_EAL_GROWTHSTRATEGY_H_INCLUDED)
#define MACHINE_EAL_GROWTHSTRATEGY_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Compiler.h"
#include "Eal/Types.h"



/// @brief Symbolic constant for a return value of Machine_Eal_getBestCapacity.
#define MACHINE_EAL_GROWTHSTRATEGY_SUCCESS (0)

/// @brief Symbolic constant for a return value of Machine_Eal_getBestCapacity.
#define MACHINE_EAL_GROWTHSTRATEGY_POSITIVEOVERFLOW (2)

// @brief Symbolic constant for a return value of Machine_Eal_getBestCapacity.
#define MACHINE_EAL_GROWTHSTRATEGY_INVALIDARGUMENT (1)



/// @brief Compute a "best" new capacity based on an old capacity, a required additional capacity, and a maximal capacity. 
/// @param oldCapacity The old capacity.
/// @param requiredAdditionalCapacity The required additional capacity.
/// @param maximalCapacity The maximal capacity.
/// @param newCapacity A pointer to a size_t variable receiving the "best" new capacity.
/// @return MACHINE_EAL_GROWTHSTRATEGY_INVALIDARGUMENT if oldCapacity > maximalCapacity.
/// @return MACHINE_EAL_GROWTHSTRATEGY_POSITIVEOVERFLOW if requiredAdditionalCapacity > maximalCapacity
/// @remark
/// This growth strategy computes the new size as follows:
/// - Let newCapacity' = oldCapacity + requiredAdditionalCapacity if that expression does not overflow.
///   Otherwise return MACHINE_EAL_GROWTHSTRATEGY_POSITIVEOVERFLOW.
/// - Let v be the least power of two greater than or equal to newCapacity' and smaller than or equal to maximalCapacity.
///   Let newCapacity'' = v and return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS if v exists.
///   Otherwise continue.
/// - If requiredNewCapacity < oldCapacity / 2:
///     Let w be 1.5 * oldCapacity smaller than or equal to maximalCapacity.
///     Let newCapacity'' = w and return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS if w exists.
///     Otherwise continue.
/// - Return MACHINE_EAL_GROWTHSTRATEGY_SUCCESS.
int Machine_Eal_getBestCapacity(size_t oldCapacity, size_t requiredAdditionalCapacity, size_t maximalCapacity, size_t* newCapacity);



#endif // MACHINE_EAL_GROWTHSTRATEGY_H_INCLUDED
