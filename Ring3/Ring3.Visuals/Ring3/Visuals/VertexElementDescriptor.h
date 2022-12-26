/// @file Ring3/Visuals/VertexElementDescriptor.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_VERTEXELEMENTDESCRIPTOR_H_INCLUDED)
#define RING3_VISUALS_VERTEXELEMENTDESCRIPTOR_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/VertexElementDescriptor.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/VertexElementSemantics.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_VertexElementDescriptor)

/// @brief Create a vertex descriptor.
/// @return The vertex descriptor.
Ring1_NoDiscardReturn() Ring3_VertexElementDescriptor*
Ring3_VertexElementDescriptor_create
  (
    Ring3_VertexElementSemantics
  );

/// @brief Get the size, in Bytes, of a vertex element.
/// @param self The vertex element descriptor.
/// @return The size, in Bytes, of the vertex.
Ring1_NoDiscardReturn() size_t
Ring3_VertexElementDescriptor_getSize
  (
    Ring3_VertexElementDescriptor* self
  );

/// @brief Get the semantics of a vertex element.
/// @param self This vertex element descriptor.
/// @return The semantics.
Ring1_NoDiscardReturn() Ring3_VertexElementSemantics
Ring3_VertexElementDescriptor_getSemantics
  (
    Ring3_VertexElementDescriptor* self
  );

#endif // RING3_VISUALS_VERTEXELEMENTDESCRIPTOR_H_INCLUDED
