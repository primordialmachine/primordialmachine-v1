/// @file Video/ProgramKind.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_PROGRAMKIND_H_INCLUDED)
#define MACHINE_VIDEO_PROGRAMKIND_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif



/// @brief Kind of a program.
typedef enum Machine_ProgramKind Machine_ProgramKind;

enum Machine_ProgramKind {

  /// @brief A vertex program.
  Machine_ProgramKind_Vertex,

  /// @brief A geometry program.
  Machine_ProgramKind_Geometry,

  /// @brief A fragment program.
  Machine_ProgramKind_Fragment,

};



#endif // MACHINE_VIDEO_PROGRAMKIND_H_INCLUDED
