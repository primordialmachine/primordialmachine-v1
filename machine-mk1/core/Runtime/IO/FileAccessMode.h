/// @file Runtime/IO/FileAccessMode.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_FILEACCESSMODE_H_INCLUDED)
#define MACHINE_RUNTIME_IO_FILEACCESSMODE_H_INCLUDED

/// @brief An enumeration of file access modes to files.
/// @remarks The enumeration elements can be combined.
typedef enum Machine_Runtime_FileAccessMode
{

  /// @brief Read access.
  /// @remark Can be combined with Nucleus_AccessMode_Write.
  Machine_Runtime_FileAccessMode_Read = 1,

  /// @brief Write access.
  /// @remark Can be combined with Nucleus_AccessMode_Read.
  Machine_Runtime_FileAccessMode_Write = 2,

  /// @brief Read and write access.
  /// @remark Alias for @code{Nucleus_FileAccessMode_Read|Nucleus_FileAccessMode_Write}.
  /// Alias for @code{Nucleus_FileAccessMode_WriteRead}.
  Machine_Runtime_FileAccessMode_FileAccessMode_ReadWrite = Machine_Runtime_FileAccessMode_Read | Machine_Runtime_FileAccessMode_Write,

  /// @brief Write and read access.
  /// @remark Alias for @code{Nucleus_FileAccessMode_Write|Nucleus_FileAccessMode_Read}.
  /// Alias for @code{Nucleus_FileAccessMode_ReadWrite}.
  Machine_Runtime_FileAccessMode_WriteRead = Machine_Runtime_FileAccessMode_Write | Machine_Runtime_FileAccessMode_Read,

} Machine_Runtime_FileAccessMode;

#endif // MACHINE_RUNTIME_IO_FILEACCESSMODE_H_INCLUDED
