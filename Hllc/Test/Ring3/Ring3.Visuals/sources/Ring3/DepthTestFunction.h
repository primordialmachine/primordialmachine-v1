/// @file Ring3/DepthTestFunction.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_DEPTHTESTFUNCTION_H_INCLUDED)
#define RING3_DEPTHTESTFUNCTION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_DepthTestFunction)

enum Ring3_DepthTestFunction
{
  Ring3_DepthTestFunction_LessThan,
  Ring3_DepthTestFunction_LessThanOrEqualTo,
  Ring3_DepthTestFunction_EqualTo,
  Ring3_DepthTestFunction_GreaterThan,
  Ring3_DepthTestFunction_GreaterThanOrEqualTo,
  Ring3_DepthTestFunction_Always,
  Ring3_DepthTestFunction_Never,
  Ring3_DepthTestFunction_NotEqual,
};

#ifdef __cplusplus
}
#endif

#endif // RING3_DEPTHTESTFUNCTION_H_INCLUDED
