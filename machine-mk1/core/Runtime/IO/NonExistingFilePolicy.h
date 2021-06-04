/// @file Runtime/IO/NonExistingFilePolicy.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO_NONEXISTINGFILEPOLICY_H_INCLUDED)
#define MACHINE_RUNTIME_IO_NONEXISTINGFILEPOLICY_H_INCLUDED

/// @brief An enumeration of policies for opening a file in case of that the file does not exist.
/// @remarks The enumeration elements can not be combined.
typedef enum Machine_Runtime_NonExistingFilePolicy
{

  /// @brief Fail.
  Machine_Runtime_NonExistingFilePolicy_Fail,

  /// @brief Create the file.
  Machine_Runtime_NonExistingFilePolicy_Create,

} Machine_Runtime_NonExistingFilePolicy;

#endif // MACHINE_RUNTIME_IO_NONEXISTINGFILEPOLICY_H_INCLUDED
