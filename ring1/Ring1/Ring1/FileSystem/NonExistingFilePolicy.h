// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/NonExistingFilePolicy.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_NONEXISTINGFILEPOLICY_H_INCLUDED)
#define RING1_FILESYSTEM_NONEXISTINGFILEPOLICY_H_INCLUDED

// https://primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_NonExistingFilePolicy
typedef enum Ring1_FileSystem_NonExistingFilePolicy {

  Ring1_FileSystem_NonExistingFilePolicy_Fail,

  Ring1_FileSystem_NonExistingFilePolicy_Create,

} Ring1_FileSystem_NonExistingFilePolicy;

#endif // RING1_FILESYSTEM_NONEXISTINGFILEPOLICY_H_INCLUDED
