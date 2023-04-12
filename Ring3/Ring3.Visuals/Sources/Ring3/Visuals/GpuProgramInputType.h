/// @file Ring3/Visuals/GpuProgramInputType.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GPUPROGRAMINPUTTYPE_H_INCLUDED)
#define RING3_VISUALS_GPUPROGRAMINPUTTYPE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuProgramInputType.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief An enumeration of types of input variables to a GPU program.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_GpuProgramInputType)

enum Ring3_GpuProgramInputType {

  /// @brief A two element single precision floating point vector.
  Ring3_GpuProgramInputType_Vector2,

  /// @brief A three element single precision floating point vector.
  Ring3_GpuProgramInputType_Vector3,

  /// @brief A four element single precision floating point vector.
  Ring3_GpuProgramInputType_Vector4,

  /// @brief A two dimensional sampler.
  Ring3_GpuProgramInputType_Sampler2,

};

#endif // RING3_VISUALS_GPUPROGRAMINPUTTYPE_H_INCLUDED
