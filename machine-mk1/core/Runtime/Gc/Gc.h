/// @file Runtime/Gc/Gc.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_GC_H_INCLUDED)
#define MACHINE_RUNTIME_GC_GC_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "_Eal.h"
#include "Runtime/Gc/Tag.h"
#include "Runtime/Status.h"



/// @brief Initialize the GC module.
Machine_StatusValue Machine_initializeGcModule();

/// @brief Uninitialize the GC module.
void Machine_uninitializeGcModule();

/// @brief Convert a pointer to an object into a pointer to the tag of the object.
/// @param src The pointer to the object.
/// @return A pointer to the tag of the object.
Machine_Gc_Tag* Machine_Gc_toTag(void* src);

/// @brief Convert a pointer to a tag into a pointer to the object of the tag.
/// @param src The pointer to the tag.
/// @return A pointer to the object of the tag.
void* Machine_Gc_toAddress(Machine_Gc_Tag* src);

/// @brief Increment the lock count of an object.
/// @param object A pointer to the object.
void Machine_Gc_lock(void* object);

/// @brief Decrement the lock count of an object.
/// @param object A pointer to the object.
void Machine_Gc_unlock(void* object);

/// @brief Set if an object is marked as a root object.
/// @undefined Invoked in visit callback or finalize callback.
void Machine_Gc_setRoot(void* object, bool isRoot);

/// @brief Get if an object is marked as a root object.
/// @param object the object.
/// @return @a true if the object is a root, @a false otherwise.
bool Machine_Gc_isRoot(void* object);

/// @brief Arguments for a call to Machine_Gc_allocate.
typedef struct Machine_Gc_AllocationArguments {

  /// @brief The size, in Bytes, of the prefix.
  size_t prefixSize;

  /// @brief The size, in Bytes, of the suffix.
  size_t suffixSize;

  /// @brief A pointer to a Machine_Gc_VisitCallback function or a null pointer.
  Machine_Gc_VisitCallback* visit;
  
  /// @brief A pointer to a Machine_Gc_FinalizeCallback function or a null pointer.
  Machine_Gc_FinalizeCallback* finalize;

} Machine_Gc_AllocationArguments;

/// @brief Allocate a GC object.
/// @param arguments A pointer to a Machine_Gc_AllocationArguments structure providing the arguments for the allocation.
/// @return A pointer to the object on success, a null pointer on failure.
void* Machine_Gc_allocate(Machine_Gc_AllocationArguments const* arguments);

/// @internal
/// @todo Move into Gc.module.h/Gc.module.c
void Machine_Gc_Tag_visit(Machine_Gc_Tag* tag);

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

#endif // MACHINE_RUNTIME_GC_GC_H_INCLUDED
