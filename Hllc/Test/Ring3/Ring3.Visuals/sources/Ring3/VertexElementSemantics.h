/// @file Ring3/VertexElementSemantics.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_VERTEXELEMENTSEMANTICS_H_INCLUDED)
#define RING3_VERTEXELEMENTSEMANTICS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_VertexElementSemantics)

enum Ring3_VertexElementSemantics
{
  Ring3_VertexElementSemantics_XfYf,
  Ring3_VertexElementSemantics_RfGfBf,
  Ring3_VertexElementSemantics_UfVf,
};

#ifdef __cplusplus
}
#endif

#endif // RING3_VERTEXELEMENTSEMANTICS_H_INCLUDED
