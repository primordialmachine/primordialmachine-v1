/// @file Ring3/Visuals/LightType.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_LIGHTTYPE_H_INCLUDED)
#define RING3_VISUALS_LIGHTTYPE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/LightType.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// Enumeration of light types.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_LightType)


/// @brief An enumeration of light types.
enum Ring3_LightType {

  /// @brief Light type "ambient".
  Ring3_LightType_Ambient,

  /// @brief Light type "directional".
  Ring3_LightType_Directional,

  /// @brief Light type "point".
  Ring3_LightType_Point,

}; // enum Ring3_LightType

#endif // RING3_VISUALS_LIGHTTYPE_H_INCLUDED
