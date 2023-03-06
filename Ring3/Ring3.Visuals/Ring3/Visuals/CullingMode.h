/// @file Ring3/Visuals/CullingMode.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_CULLINGMODE_H_INCLUDED)
#define RING3_VISUALS_CULLINGMODE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/CullingMode.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// Enumeration of culling modes.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_CullingMode)

enum Ring3_CullingMode {

  /// @brief Neither back faces nor front faces are culled.
  Ring3_CullingMode_None,
  
  /// @brief Front faces are culled. Back faces are not culled.
  Ring3_CullingMode_Front,
  
  /// @brief Back faces are culled. Front faces are not culled.
  Ring3_CullingMode_Back,
  
  /// @brief Both back faces and front faces are culled.
  Ring3_CullingMode_BackAndFront,

};

#endif // RING3_VISUALS_CULLINGMODE_H_INCLUDED
