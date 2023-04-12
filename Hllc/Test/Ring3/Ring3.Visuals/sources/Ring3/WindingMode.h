/// @file Ring3/WindingMode.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_WINDINGMODE_H_INCLUDED)
#define RING3_WINDINGMODE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_WindingMode)

enum Ring3_WindingMode
{
  Ring3_WindingMode_Clockwise,
  Ring3_WindingMode_CounterClockwise,
};

#ifdef __cplusplus
}
#endif

#endif // RING3_WINDINGMODE_H_INCLUDED
