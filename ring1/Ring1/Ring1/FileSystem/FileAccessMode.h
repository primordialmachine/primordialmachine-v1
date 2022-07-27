// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/FileAccessMode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_FILEACCESSMODE_H_INCLUDED)
#define RING1_FILESYSTEM_FILEACCESSMODE_H_INCLUDED

// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_FileAccessMode
typedef enum Ring1_FileSystem_FileAccessMode
{

  Ring1_FileSystem_FileAccessMode_Read = 1,

  Ring1_FileSystem_FileAccessMode_Write = 2,

  Ring1_FileSystem_FileAccessMode_ReadWrite =
    Ring1_FileSystem_FileAccessMode_Read | Ring1_FileSystem_FileAccessMode_Write,

  Ring1_FileSystem_FileAccessMode_WriteRead =
    Ring1_FileSystem_FileAccessMode_Write | Ring1_FileSystem_FileAccessMode_Read,

} Ring1_FileSystem_FileAccessMode;

#endif // RING1_FILESYSTEM_FILEACCESSMODE_H_INCLUDED
