/// @file Runtime/Machine.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_H_INCLUDED)
#define MACHINE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "Runtime/Assertions.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/StackModule.h"
#include "Runtime/LogModule.h"
#include "Runtime/StaticVariablesModule.h"

#include "Runtime/PrimitiveTypes.h"
#include "Runtime/Status.h"
#include "Runtime/Value.h"

#include "Runtime/Gc/Gc.h"
#include "Runtime/Object/ClassType.h"
#include "Runtime/Object/Object.h"



/// @brief Startup the machine.
/// @warning Undefined if the machine is already initialized.
/// @return #Machine_Status_Success on success, a non-zero Machine_Status value on failure.
Machine_StatusValue Machine_startup();

/// @brief Shutdown the machine.
/// Finalize and deallocate all objects.
/// @warning Undefined if the machine is already uninitialized.
void Machine_shutdown();

/// @brief Update the machine.
void Machine_update();

#endif // MACHINE_H_INCLUDED