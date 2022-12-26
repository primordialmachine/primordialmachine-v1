/// @file Ring3/Visuals/GpuProgramInputType.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GPUPROGRAMINPUTKIND_H_INCLUDED)
#define RING3_VISUALS_GPUPROGRAMINPUTKIND_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuProgramInputKind.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief An enumeration of kinds of input variables to a GPU program.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_GpuProgramInputKind)

enum Ring3_GpuProgramInputKind {
  /// @brief A constant input (e.g., for all vertices, for all fragments, ...).
  Ring3_GpuProgramInputKind_Constant,
  /// @brief A variable input (e.g., per vertex, per fragment, ...).
  Ring3_GpuProgramInputKind_Variable,
};

#endif // RING3_VISUALS_GPUPROGRAMINPUTKIND_H_INCLUDED
