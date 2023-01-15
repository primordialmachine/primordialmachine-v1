// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC__INCLUDE_H_INCLUDED)
#define RING1_INTRINSIC__INCLUDE_H_INCLUDED

#define RING1_INTRINSIC_PRIVATE (1)
#include "Ring1/Intrinsic/atomicCompareExchange.h"
#include "Ring1/Intrinsic/atomicDecrement.h"
#include "Ring1/Intrinsic/atomicGet.h"
#include "Ring1/Intrinsic/atomicIncrement.h"
#include "Ring1/Intrinsic/Add/add.h"
#include "Ring1/Intrinsic/ByteOrder.h"
#include "Ring1/Intrinsic/clamp.h"
#include "Ring1/Intrinsic/countDecimalDigits.h"
#include "Ring1/Intrinsic/Concurrency/ReadWriteLock.h"
#include "Ring1/Intrinsic/CountLeadingZeroes/countLeadingZeroes.h"
#include "Ring1/Intrinsic/FloatingPointTypes.h"
#include "Ring1/Intrinsic/isPowerOfTwo.h"
#include "Ring1/Intrinsic/lerp.h"
#include "Ring1/Intrinsic/Multiply/multiply.h"
#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"
#include "Ring1/Intrinsic/NextMultipleOf32/nextMultipleOf32.h"
#include "Ring1/Intrinsic/NextMultipleOf64/nextMultipleOf64.h"
#include "Ring1/Intrinsic/Subtract/subtract.h"
#include "Ring1/Intrinsic/ThreadLocal.h"
#undef RING1_INTRINSIC_PRIVATE

/// @brief Macro unconditionally casting an expression into a type.
/// @param t The type.
/// @param e The expression.
/// @remark
/// @code
/// Ring1_cast(T,e)
/// @endcode
/// is equivalent to
/// @code
/// ((T)(E))
/// @endcode
#define Ring1_cast(t,e) ((t)(e))

#endif // RING1_INTRINSIC__INCLUDE_H_INCLUDED
