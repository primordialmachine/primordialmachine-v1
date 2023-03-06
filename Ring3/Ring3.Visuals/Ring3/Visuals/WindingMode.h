/// @file Ring3/Visuals/WindingMode.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_WINDINGMODE_H_INCLUDED)
#define RING3_VISUALS_WINDINGMODE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/WindingMode.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// Enumeration of winding modes.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_WindingMode)

enum Ring3_WindingMode {

  /// @brief Clockwise winding mode.
  Ring3_WindingMode_Clockwise,

  /// @brief Counter clockwise winding mode.
  Ring3_WindingMode_CounterClockwise,

};

#endif // RING3_VISUALS_WINDINGMODE_H_INCLUDED
