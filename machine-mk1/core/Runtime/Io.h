/// @file Runtime/Io.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_H_INCLUDED)
#define MACHINE_RUNTIME_IO_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "Runtime/Io/ExistingFilePolicy.h"
#include "Runtime/Io/FileAccessMode.h"
#include "Runtime/Io/getFileContents.h"
#include "Runtime/Io/NonExistingFilePolicy.h"
#include "Runtime/Io/setFileContents.h"



#endif // MACHINE_RUNTIME_IO_H_INCLUDED
