/// @file Ring3/Visuals/GpuProgramInputDescriptor.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GPUPROGRAMINPUTDESCRIPTOR_H_INCLUDED)
#define RING3_VISUALS_GPUPROGRAMINPUTDESCRIPTOR_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuProgramInputDescriptor.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/GpuProgramInputKind.h"
#include "Ring3/Visuals/GpuProgramInputType.h"

/// @brief Description of an input variable of a GPU program.
MACHINE_DECLARE_CLASSTYPE(Ring3_GpuProgramInputDescriptor)

struct Ring3_GpuProgramInputDescriptor_Class {
  Machine_Object_Class parent;
};

struct Ring3_GpuProgramInputDescriptor {
  Machine_Object parent;
  Ring2_String* name;
  Ring3_GpuProgramInputType type;
  Ring3_GpuProgramInputKind kind;
};

/// @brief Create a program input (descriptor).
/// @param name The name of the program input.
/// @param type The type of the program input.
/// @param kind The kind of the program input.
/// @return The program input.
Ring1_NoDiscardReturn() Ring3_GpuProgramInputDescriptor*
Ring3_GpuProgramInputDescriptor_create
  (
    Ring2_String* name,
    Ring3_GpuProgramInputType type,
    Ring3_GpuProgramInputKind kind
  );

#endif // RING3_VISUALS_GPUPROGRAMINPUTDESCRIPTOR_H_INCLUDED
