/// @file Images.package.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_IMAGES_PACKAGE_H_INCLUDED)
#define MACHINE_IMAGES_PACKAGE_H_INCLUDED

#include "_Runtime.h"

/// @brief Increment the image module by @a 1.
/// @error The reference count s #Machine_Integer_Greatest.
void Machine_Images_startup();

/// @brief Decrement the images module by @a 1.
/// @undefined The reference count was @a 0.
void Machine_Images_shutdown();

#endif // MACHINE_IMAGES_PACKAGE_H_INCLUDED
