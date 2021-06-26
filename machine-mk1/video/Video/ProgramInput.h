/// @file Video/ProgramInput.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_PROGRAMINPUT_H_INCLUDED)
#define MACHINE_VIDEO_PROGRAMINPUT_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif



#include "./../Video/ProgramInputType.h"


/// @brief Description of a constant or variable input to a program.
MACHINE_DECLARE_CLASSTYPE(Machine_ProgramInput)

struct Machine_ProgramInput {
  Machine_Object parent;
  Machine_String* name;
  Machine_ProgramInputType type;
};

/// @brief Create a program input (descriptor).
/// @param name The name of the program input.
/// @param type The type of the program input.
/// @return The program input.
Machine_ProgramInput* Machine_ProgramInput_create(Machine_String* name, Machine_ProgramInputType type);



#endif // MACHINE_VIDEO_PROGRAMINPUT_H_INCLUDED
