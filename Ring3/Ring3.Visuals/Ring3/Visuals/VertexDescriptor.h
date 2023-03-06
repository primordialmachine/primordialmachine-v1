/// @file Ring3/Visuals/VertexDescriptor.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_VERTEXDESCRIPTOR_H_INCLUDED)
#define RING3_VISUALS_VERTEXDESCRIPTOR_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/VertexDescriptor.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/VertexElementSemantics.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_VertexDescriptor)

/// @brief Create a vertex descriptor.
/// @return The vertex descriptor.
Ring1_NoDiscardReturn() Ring3_VertexDescriptor*
Ring3_VertexDescriptor_create
  (
  );

/// @brief Get the size, in Bytes, of the vertex.
/// @param self The vertex descriptor.
/// @return The size, in Bytes, of the vertex.
Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VertexDescriptor_getVertexSize
  (
    Ring3_VertexDescriptor* self
  );

/// Get the number of vertex elements.
/// @param self This vertex descriptor.
/// @return The number of vertex elements.
Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VertexDescriptor_getNumberOfElements
  (
    Ring3_VertexDescriptor* self
  );

/// @brief Get the semantics of a vertex element.
/// @param self This vertex descriptor.
/// @param index The index of the vertex element.
/// @return The semantics.
Ring1_NoDiscardReturn() Ring3_VertexElementSemantics
Ring3_VertexDescriptor_getElementSemantics
  (
    Ring3_VertexDescriptor* self,
    Ring2_Integer index
  );

/// @brief Get the offset of a vertex element.
/// @param self This vertex descriptor.
/// @param index The index of the vertex element.
/// @return The offset.
Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VertexDescriptor_getElementOffset
  (
    Ring3_VertexDescriptor* self,
    Ring2_Integer index
  );

void
Ring3_VertexDescriptor_insert
  (
    Ring3_VertexDescriptor* self,
    Ring2_Integer index,
    Ring3_VertexElementSemantics semantics
  );

void
Ring3_VertexDescriptor_append
  (
    Ring3_VertexDescriptor* self,
    Ring3_VertexElementSemantics semantics
  );

void
Ring3_VertexDescriptor_prepend
  (
    Ring3_VertexDescriptor* self,
    Ring3_VertexElementSemantics semantics
  );

#endif // RING3_VISUALS_VERTEXDESCRIPTOR_H_INCLUDED
