// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Test/createDirectory.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_TEST_CREATEDIRECTORY_H_INCLUDED)
#define RING1_FILESYSTEM_TEST_CREATEDIRECTORY_H_INCLUDED

#include "Ring1/Test.h"
#include "Ring1/All/_Include.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_registerCreateDirectoryTests
  (
    Ring1_Test_Context* ctx
  );

#endif // RING1_FILESYSTEM_TEST_CREATEDIRECTORY_H_INCLUDED
