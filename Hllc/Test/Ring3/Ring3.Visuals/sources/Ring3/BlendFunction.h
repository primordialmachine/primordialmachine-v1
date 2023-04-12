/// @file Ring3/BlendFunction.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_BLENDFUNCTION_H_INCLUDED)
#define RING3_BLENDFUNCTION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_BlendFunction)

enum Ring3_BlendFunction
{
  Ring3_BlendFunction_IncomingColour,
  Ring3_BlendFunction_OneMinusIncomingColour,
  Ring3_BlendFunction_ExistingColour,
  Ring3_BlendFunction_OneMinusExistingColour,
  Ring3_BlendFunction_IncomingAlpha,
  Ring3_BlendFunction_OneMinusIncomingAlpha,
  Ring3_BlendFunction_ExistingAlpha,
  Ring3_BlendFunction_OneMinusExistingAlpha,
  Ring3_BlendFunction_Zero,
  Ring3_BlendFunction_One,
};

#ifdef __cplusplus
}
#endif

#endif // RING3_BLENDFUNCTION_H_INCLUDED
