/// @file Runtime/Machine.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_MACHINE_H_INCLUDED)
#define MACHINE_RUNTIME_MACHINE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Machine.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring1/Result.h"

/// @brief Startup the machine.
/// @warning Undefined if the machine is already initialized.
/// @return #Machine_Status_Success on success, a non-zero Machine_Status value on failure.
Ring1_Result Machine_startup();

/// @brief Shutdown the machine.
/// Finalize and deallocate all objects.
/// @warning Undefined if the machine is already uninitialized.
void Machine_shutdown();

/// @brief Update the machine.
void Machine_update();

#endif // MACHINE_RUNTIME_MACHINE_H_INCLUDED
