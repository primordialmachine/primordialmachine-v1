/// @file Ring3/Visuals/VertexElementSemantics.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_VERTEXELEMENTSEMANTICS_H_INCLUDED)
#define RING3_VISUALS_VERTEXELEMENTSEMANTICS_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/VertexElementSemantics.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief Semantics of a vertex element.
MACHINE_DECLARE_ENUMERATIONTYPE(Machine_VertexElementSemantics)

enum Machine_VertexElementSemantics {
  /// @brief Vertex element consists of sub-elements "x" and "y" in that order.
  /// All sub-elements are of type float.
  Machine_VertexElementSemantics_XfYf,

  /// @brief Vertex element consists of sub-elements "r", "g", and "b" in that order.
  /// All sub-elements are of type float and within the bounds of 0 (inclusive) and 1 (inclusive).
  Machine_VertexElementSemantics_RfGfBf,

  /// @brief Vertex element consists of sub-elements "u" and "v" in that order.
  /// All sub-elements are of type float.
  Machine_VertexElementSemantics_UfVf,
};

#endif // RING3_VISUALS_VERTEXELEMENTSEMANTICS_H_INCLUDED
