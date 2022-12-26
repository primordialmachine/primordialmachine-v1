/// @file Ring3/Visuals/GpuProgramKind.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GPUPROGRAMKIND_H_INCLUDED)
#define RING3_VISUALS_GPUPROGRAMKIND_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuProgramKind.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief An enumeration of kinds of GPU programs.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_GpuProgramKind)

enum Ring3_GpuProgramKind {

  /// @brief A GPU vertex program.
  Ring3_GpuProgramKind_Vertex,

  /// @brief A GPU geometry program.
  Ring3_GpuProgramKind_Geometry,

  /// @brief A GPU fragment program.
  Ring3_GpuProgramKind_Fragment,

};

#endif // RING3_VISUALS_GPUPROGRAMKIND_H_INCLUDED
