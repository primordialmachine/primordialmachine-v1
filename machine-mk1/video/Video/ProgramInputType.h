/// @file Video/ProgramInputType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_PROGRAMINPUTTYPE_H_INCLUDED)
#define MACHINE_VIDEO_PROGRAMINPUTTYPE_H_INCLUDED

#include "Video/_header.i"

/// @brief An enumeration of types of shader inputs.
MACHINE_DECLARE_ENUMERATIONTYPE(Machine_ProgramInputType)

enum Machine_ProgramInputType {
  /// @brief A two element single precision floating point vector.
  Machine_ProgramInputType_Vector2,
  /// @brief A three element single precision floating point vector.
  Machine_ProgramInputType_Vector3,
  /// @brief A four element single precision floating point vector.
  Machine_ProgramInputType_Vector4,
  /// @brief A two dimensional sampler.
  Machine_ProgramInputType_Sampler2,
};

#endif // MACHINE_VIDEO_PROGRAMINPUTTYPE_H_INCLUDED
