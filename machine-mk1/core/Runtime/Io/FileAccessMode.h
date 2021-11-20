/// @file Runtime/Io/FileAccessMode.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_FILEACCESSMODE_H_INCLUDED)
#define MACHINE_RUNTIME_IO_FILEACCESSMODE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

/// @brief An enumeration of file access modes to files.
/// @remarks The enumeration elements can be combined.
typedef enum Machine_FileAccessMode
{

  /// @brief Read access.
  /// @remark Can be combined with Machine_AccessMode_Write.
  Machine_FileAccessMode_Read = 1,

  /// @brief Write access.
  /// @remark Can be combined with Machine_AccessMode_Read.
  Machine_FileAccessMode_Write = 2,

  /// @brief Read and write access.
  /// @remark Alias for @code{Machine_FileAccessMode_Read|Machine_FileAccessMode_Write}.
  /// Alias for @code{Machine_FileAccessMode_WriteRead}.
  Machine_FileAccessMode_ReadWrite = Machine_FileAccessMode_Read | Machine_FileAccessMode_Write,

  /// @brief Write and read access.
  /// @remark Alias for @code{Machines_FileAccessMode_Write|Machine_FileAccessMode_Read}.
  /// Alias for @code{Machine_FileAccessMode_ReadWrite}.
  Machine_FileAccessMode_WriteRead = Machine_FileAccessMode_Write | Machine_FileAccessMode_Read,

} Machine_FileAccessMode;

#endif // MACHINE_RUNTIME_IO_FILEACCESSMODE_H_INCLUDED
