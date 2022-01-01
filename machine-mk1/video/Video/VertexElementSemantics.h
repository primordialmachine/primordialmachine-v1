/// @file Video/VertexElementSemantics.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_VERTEXELEMENTSEMANTICS_H_INCLUDED)
#define MACHINE_VIDEO_VERTEXELEMENTSEMANTICS_H_INCLUDED

#include "Video/_header.i"

/// @brief Semantics of a vertex element.
typedef enum Machine_VertexElementSemantics Machine_VertexElementSemantics;

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

#endif // MACHINE_VIDEO_VERTEXELEMENTSEMANTICS_H_INCLUDED
