/// @file _Images.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_IMAGES_PRIVATE (1)
#include "_Images.h"
#include "ImagesContext.h"



Machine_ImagesContext* Machines_DefaultImages_createContext() {
  return (Machine_ImagesContext*)Machine_Images_ImagesContext_create();
}
