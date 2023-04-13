// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/ReceiveCallback.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_RECEIVECALLBACK_H_INCLUDED)
#define RING1_FILESYSTEM_RECEIVECALLBACK_H_INCLUDED

#include "Ring1/Result.h"
#include <stddef.h>

// Callback invoked when n Bytes pointed to by p should be appended to an opaque context.
typedef Ring1_Result(Ring1_FileSystem_ReceiveCallback)(void* context, void* p, size_t n);

#endif // RING1_FILESYSTEM_RECEIVECALLBACK_H_INCLUDED
