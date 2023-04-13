// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/ExistingFilePolicy.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_EXISTINGFILEPOLICY_H_INCLUDED)
#define RING1_FILESYSTEM_EXISTINGFILEPOLICY_H_INCLUDED

// https://primordialmachine.com/api/ring1-library/filesystem-library/Ring1_FileSystem_ExistingFilePolicy
typedef enum Ring1_FileSystem_ExistingFilePolicy {

  Ring1_FileSystem_ExistingFilePolicy_Retain,

  Ring1_FileSystem_ExistingFilePolicy_Truncate,

} Ring1_FileSystem_ExistingFilePolicy;

#endif // RING1_FILESYSTEM_EXISTINGFILEPOLICY_H_INCLUDED
