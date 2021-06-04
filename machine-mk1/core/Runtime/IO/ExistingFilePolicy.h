/// @file Runtime/IO/ExistingFilePolicy.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_EXISTINGFILEPOLICY_H_INCLUDED)
#define MACHINE_RUNTIME_IO_EXISTINGFILEPOLICY_H_INCLUDED

/// @brief An enumeration of policies for opening a file in case of that the file exists.
/// @remarks The enumeration elements can not be combined.
typedef enum Machine_Runtime_ExistingFilePolicy
{

  /// @brief Retaint the file.
  Machine_Runtime_ExistingFilePolicy_Retain,

  /// @brief Truncate the file.
  Machine_Runtime_ExistingFilePolicy_Truncate,

} Machine_Runtime_ExistingFilePolicy;

#endif // MACHINE_RUNTIME_IO_EXISTINGFILEPOLICY_H_INCLUDED
