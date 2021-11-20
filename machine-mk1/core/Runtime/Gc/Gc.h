/// @file Runtime/Gc/Gc.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_GC_H_INCLUDED)
#define MACHINE_RUNTIME_GC_GC_H_INCLUDED



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
INLINE Machine_Tag* Machine_o2t(void* src);

/// @brief Convert a pointer to a tag into a pointer to the object of the tag.
/// @param src The pointer to the tag.
/// @return A pointer to the object of the tag.
INLINE void* Machine_t2o(Machine_Tag* src);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

INLINE Machine_Tag* Machine_o2t(void* src) {
  static const size_t N = sizeof(Machine_Tag);
  char* dst = ((char*)src) - N;
  return (Machine_Tag*)dst;
}

INLINE void* Machine_t2o(Machine_Tag* src) {
  static const size_t N = sizeof(Machine_Tag);
  char* dst = ((char*)src) + N;
  return (void*)dst;
}

/// @brief Increment the lock count of an object.
/// @param object A pointer to the object.
void Machine_lock(void* object);

/// @brief Decrement the lock count of an object.
/// @param object A pointer to the object.
void Machine_unlock(void* object);

/// @brief Set if an object is marked as a root object.
/// @undefined Invoked in visit callback or finalize callback.
void Machine_setRoot(void* object, bool isRoot);

/// @brief Get if an object is marked as a root object.
/// @param object the object.
/// @return @a true if the object is a root, @a false otherwise.
bool Machine_isRoot(void* object);

/// @brief Allocate a payload.
/// @param tagPrefixSize The size, in Bytes, of the tag prefix.
/// @param payloadSize The size, in Bytes, of the payload.
/// @param visit A pointer to the Machine_VisitCallback function for the object or a null pointer.
/// @param finalize A pointer to the Machine_FinalizeCallback function for the object or a null pointer.
/// @return A pointer to the object on success, a null pointer on failure.
void* Machine_allocateEx(size_t payloadSize, size_t tagPrefixSize, Machine_VisitCallback* visit, Machine_FinalizeCallback* finalize);



#endif // MACHINE_RUNTIME_GC_GC_H_INCLUDED
