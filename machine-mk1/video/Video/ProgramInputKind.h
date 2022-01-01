/// @file Video/ProgramInputType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_PROGRAMINPUTKIND_H_INCLUDED)
#define MACHINE_VIDEO_PROGRAMINPUTKIND_H_INCLUDED

#include "Video/_header.i"

/// @brief An enumeration of kind of shader inputs.
typedef enum Machine_ProgramInputKind Machine_ProgramInputKind;

enum Machine_ProgramInputKind {
  /// @brief A constant input.
  Machine_ProgramInputKind_Constant,
  /// @brief A variable input.
  Machine_ProgramInputKind_Variable,
};

#endif // MACHINE_VIDEO_PROGRAMINPUTKIND_H_INCLUDED
