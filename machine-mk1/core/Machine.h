/// @file Machine.h
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

#include "Runtime/GC/GC.h"
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/// @brief Allocate a payload.
/// @param size The size, in Bytes, of the payload.
/// @param visit A pointer to the Machine_VisitCallback function for the object or a null pointer.
/// @param finalize A pointer to the Machine_FinalizeCallback function for the object or a null pointer.
/// @return A pointer to the object on success, a null pointer on failure.
void* Machine_Gc_allocate(size_t size, Machine_VisitCallback *visit, Machine_FinalizeCallback *finalize);

/// @brief Visit an object.
/// @param object A pointer to the object.
/// @undefined Invoked outside of visit callback.
void Machine_Gc_visit(void* object);

/// @brief Run the GC.
/// @param live Pointer to a variable receiving the number of live objects or a null pointer.
/// @param dead Pointer to a variable receiving the number of dead objects or a null pointer.
/// @success @a *live was assigned the number of objects alive after this run.
/// @success @a *dead was assigned the number of objects dead after this run.
void Machine_Gc_run(size_t* live, size_t* dead);



#endif // MACHINE_H_INCLUDED
