// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Real.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_REAL_H_INCLUDED)
#define RING2_TYPES_REAL_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

#include <float.h>



/// @brief The C-level representation of the "Real32" type.
typedef float Ring2_Real32;

/// @brief Symbolic constant evaluating to the C-level representation of the
/// "Real32.Greatest" value.
#define Ring2_Real32_Greatest (+FLT_MAX)

/// @brief Symbolic constant evaluating to the C-level representation of the
/// "Real32.Least" value.
#define Ring2_Real32_Least (-FLT_MAX)

/// @brief Symbolic constant evaluating to the C-level representation of the
/// "Real32.NoNumber" value.
#define Ring2_Real32_NoNumber (NAN)

/// @brief Symbolic constant evaluating to the C-level representation of the
/// "Real32.PositiveInfinity" value.
#define Ring2_Real32_PositiveInfinity (+INF)

/// @brief Symbolic constant evaluating to the C-level representation of the
/// "Real.NegativeInfinity" value.
#define Ring2_Real32_NegativeInfinity (-INF)



/// @brief The C-level representation of the "Real64" type.
typedef double Ring2_Real64;

/// @brief Symbolic constant evaluating to the C-level representation of the "Real.Greatest" value.
#define Ring2_Real64_Greatest (+DBL_MAX)

/// @brief Symbolic constant evaluating to the C-level representation of the "Real.Least" value.
#define Ring2_Real64_Least (-DLB_MAX)

/// @brief Symbolic constant evaluating to the C-level representation of the "Real.NoNumber" value.
#define Ring2_Real64_NoNumber (NAN)

/// @brief Symbolic constant evaluating to the C-level representation of the "Real.PositiveInfinity" value.
#define Ring2_Real64_PositiveInfinity (+INF)

/// @brief Symbolic constant evaluating to the C-level representation of the "Real.NegativeInfinity" value.
#define Ring2_Real64_NegativeInfinity (-INF)



#endif // Ring2_Configuration_withReal

#endif // RING2_TYPES_REAL_H_INCLUDED
