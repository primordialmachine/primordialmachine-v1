// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/MemoryCallbacks.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_MEMORYCALLBACKS_H_INCLUDED)
#define RING1_FILESYSTEM_MEMORYCALLBACKS_H_INCLUDED

#include "Ring1/Result.h"
#include <stddef.h>

// https://primordialmachine.com/api/ring1-library/filesystem-library/Ring1_FileSystem_AllocateCallback
typedef Ring1_Result(Ring1_FileSystem_AllocateCallback)(void** p, size_t n);

// https://primordialmachine.com/api/ring1-library/filesystem-library/Ring1_FileSystem_DeallocateCallback
typedef Ring1_Result(Ring1_FileSystem_DeallocateCallback)(void* p);

#endif // RING1_FILESYSTEM_MEMORYCALLBACKS_H_INCLUDED
