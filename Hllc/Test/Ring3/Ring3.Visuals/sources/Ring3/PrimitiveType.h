/// @file Ring3/PrimitiveType.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_PRIMITIVETYPE_H_INCLUDED)
#define RING3_PRIMITIVETYPE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_PrimitiveType)

enum Ring3_PrimitiveType
{
  Ring3_PrimitiveType_Quadriliterals,
  Ring3_PrimitiveType_Triangles,
};

#ifdef __cplusplus
}
#endif

#endif // RING3_PRIMITIVETYPE_H_INCLUDED
