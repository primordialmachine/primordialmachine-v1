/// @file Ring3/Visuals/PrimitiveType.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_PRIMITIVETYPE_H_INCLUDED)
#define RING3_VISUALS_PRIMITIVETYPE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/PrimitiveType.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// Enumeration of primitive types.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_PrimitiveType)

enum Ring3_PrimitiveType {

  /// @brief A list of triangles.
  /// @remarks
  /// Number of vertices must be divisible by three or the number of vertices must be \f$0\f$.
  /// Given \f$3N\f$ vertices, \f$N\f$ triangles are rendered where vertices
  /// \f$3i + 0\f$, \f$3i + 1\f$, \f$3i + 2\f$ constitute triangle \f$i\f$.
  Ring3_PrimitiveType_Triangles,

  /// @brief A list of points.
  /// Given \f$N\f$ vertices, \f$N\f$ points are rendered.
  Ring3_PrimitiveType_Points,

  /// @brief A list of lines.
  /// Number of vertices must be divisible by \f$2\f$ or the number of vertices must be \f$0\f$.
  /// Given \f$2N\f$ vertices, \f$N\f$ lines are rendered where vertices
  /// \f$2i + 0\f$ and \f$2i + 1\f$ constitute line \f$i\f$.
  Ring3_PrimitiveType_Lines,

  /// @brief List of quadriliterals.
  /// Number of vertices must be divisible by four or he number of vertices must be \f$0\f$.
  /// Given \f$4N\f$ vetices, \f$N\f$ quadriliterals are rendered where vertices
  /// \f$3i + 0\f$, \f$3i + 1\f$, \f$3i + 2\f$, \f$3i + 3\f$ constitute quadriliteral \f$i\f$.
  Ring3_PrimitiveType_Quadriliterals,

};

#endif // RING3_VISUALS_PRIMITIVETYPE_H_INCLUDED
