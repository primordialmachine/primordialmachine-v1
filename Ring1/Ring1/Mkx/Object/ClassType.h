// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/ClassType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CLASSTYPE_H_INCLUDED)
#define RING1_CLASSTYPE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/ClassType.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/Type.h"
#include "Mkx/Object/Dispatch.h"
#include "Mkx/Object/InterfaceImplementation.h"
#include "Mkx/Object/MemoryManager.h"

typedef struct Mkx_Object Mkx_Object;
typedef struct Mkx_Object_Dispatch Mkx_Object_Dispatch;
typedef struct Mkx_Interface_Dispatch Mkx_Interface_Dispatch;

#define MKX_OBJECT_DESTRUCTDISPATCHFUNCTION(pointer) ((Mkx_Object_DestructDispatchFunction *)(pointer))
typedef void (Mkx_Object_DestructDispatchFunction)(Mkx_Object_Dispatch* self);

#define MKX_OBJECT_CONSTRUCTDISPATCHFUNCTION(pointer) ((Mkx_Object_ConstructDispatchFunction *)(pointer))
typedef int (Mkx_Object_ConstructDispatchFunction)(Mkx_Object_Dispatch* self);


#define MKX_CLASSTYPE(pointer) ((Mkx_ClassType *)(pointer))
typedef struct Mkx_ClassType Mkx_ClassType;


//
typedef struct Mkx_ClassTypeRegistrationInfo
{
  const char* name;
  bool instantiable;
  size_t size;
  Mkx_Type* parent;
  void (*destruct)(void* object);
  Mkx_MemoryManager* memoryManager;

  size_t dispatchSize;
  Mkx_Object_ConstructDispatchFunction* constructDispatch;
  Mkx_Object_DestructDispatchFunction* destructDispatch;
} Mkx_ClassTypeRegistrationInfo;

typedef struct Mkx_InterfaceImplementationInfo
{
  Mkx_Type* interfaceType;
  void (*construct)(Mkx_Interface_Dispatch* dispatch);
} Mkx_InterfaceImplementationInfo;

/// @brief Add an implementation of an interface to a class.
/// If there is already an implementation of the interface in this class, it is overriden.
/// @param self The class type.
/// @param interface the interface type.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_result_Failure on failure.
Ring1_CheckReturn() Ring1_Result
Mkx_ClassType_addInterfaceImplementation
  (
    Mkx_ClassType *self,
    Mkx_InterfaceType *interface,
    void (*construct)(Mkx_Interface_Dispatch *dispatch)
  );

Ring1_CheckReturn() Ring1_Result
Mkx_ClassType_hasInterfaceImplementation
  (
    bool *result,
    const Mkx_ClassType* self,
    const Mkx_InterfaceType* interface
  );

/// @brief Get the parent class type of this class type.
/// @param result A pointer to a <code>Mkx_ClassType *</code> variable.
/// @param self A pointer to this class type.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
/// @success
/// - If this class type has a parent class type,
///   <code>*result</code> was assigned a pointer the parent class type.
/// - Otherwise it was assigned the null pointer.
Ring1_CheckReturn() Ring1_Result
Mkx_ClassType_getParentClassType
  (
    Mkx_ClassType **result,
    Mkx_ClassType *self
  );

#endif // RING1_CLASSTYPE_H_INCLUDED
