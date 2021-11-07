/// @file _Eal.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE__EAL_H_INCLUDED)
#define MACHINE__EAL_H_INCLUDED



#define MACHINE_EAL_PRIVATE (1)
#include "./Eal/addSafe.h"
#include "./Eal/GrowthStrategy.h"
#include "./Eal/isPowerOfTwo.h"
#include "./Eal/leastPowerOfTwoGreaterThanOrEqualTo.h"
#include "./Eal/maximum.h"
#include "./Eal/Memory.h"
#include "./Eal/minimum.h"
#include "./Eal/multiplySafe.h"
#include "./Eal/Types.h"
#include "./Eal/Zts.h"
#undef MACHINE_EAL_PRIVATE



#endif // MACHINE__EAL_H_INCLUDED
