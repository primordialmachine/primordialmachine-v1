/// @file Ring1/FileSystem.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
#if !defined(RING1_FILESYSTEM_H_INCLUDED)
#define RING1_FILESYSTEM_H_INCLUDED

#define RING1_PRIVATE (1)
#include "Ring1/FileSystem/ExistingFilePolicy.h"
#include "Ring1/FileSystem/FileAccessMode.h"
#include "Ring1/FileSystem/NonExistingFilePolicy.h"
#undef RING1_PRIVATE

#endif // RING1_FILESYSTEM_H_INCLUDED
