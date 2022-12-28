/// @file _Images.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_IMAGES_PRIVATE (1)
#include "_Images.h"
#include "ImagesContext.h"



Ring3_ImagesContext* Machines_DefaultImages_createContext() {
  return (Ring3_ImagesContext*)Machine_Images_ImagesContext_create();
}
