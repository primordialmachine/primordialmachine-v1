// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/ClassType.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/Type.internal.h"
#include "Mkx/Object/Utilities/error.h"
#undef MKX_OBJECT_INTERNAL

#include "Ring1/Status.h"
#include "Ring1/Memory/_Include.h" /// @todo Move into "Mkx/Object/Common.internal.h".

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


Ring1_CheckReturn() Ring1_Result
Mkx_ClassType_addInterfaceImplementation
  (
    Mkx_ClassType* self,
    Mkx_InterfaceType* interface,
    void (*construct)(Mkx_Interface_Dispatch* dispatch)
  )
{
  if (Ring1_Unlikely(!self || !interface)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // The class type must not be initialized.
  if (Mkx_ClassType_isInitialized(self)) {
    char* p; int64_t n;
    if (Ring1_Unlikely(!Ring1_Atom_getBytes(&p, MKX_DISPATCH(self)->type->name) &&
                       !Ring1_Atom_getNumberOfBytes(&n, MKX_DISPATCH(self)->type->name))) {
      error_f("%s:%d: class type `%.*s`: already initialized.", __FILE__, __LINE__, n, p);
    }
    Ring1_Status_set(Ring1_Status_Initialized);
    return Ring1_Result_Failure;
  }
  // Override existing implementation if there is any.
  for (size_t i = 0, n = (size_t)self->implementations.size; i < n; ++i) {
    InterfaceImplementation* impl = &(self->implementations.elements[i]);
    if (impl->interface == interface) { 
      impl->construct = construct;
      return Ring1_Result_Success;
    }
  }
  // No implementation exists. Add it.
  InterfaceImplementation* elements = NULL;
  if (Ring1_Memory_reallocateArray(&elements,
                                   self->implementations.elements,
                                   (size_t)self->implementations.size + 1,
                                   sizeof(InterfaceImplementation))) {
    char* p; int64_t n;
    if (Ring1_Unlikely(!Ring1_Atom_getBytes(&p, MKX_DISPATCH(self)->type->name) &&
                       !Ring1_Atom_getNumberOfBytes(&n, MKX_DISPATCH(self)->type->name))) {
      error_f("%s:%d: class type `%.*s`: allocation failed.", __FILE__, __LINE__, n, p);
    }
    return Ring1_Result_Failure;
  }
  self->implementations.elements = elements;
  InterfaceImplementation *element = &(self->implementations.elements[self->implementations.size++]);
  element->construct = construct;
  element->interface = interface;
  // Return success.
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_ClassType_hasInterfaceImplementation
  (
    bool *result,
    const Mkx_ClassType* self,
    const Mkx_InterfaceType* interface
  )
{
  if (Ring1_Unlikely(!result || !self || !interface)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  for (size_t i = 0, n = (size_t)self->implementations.size; i < n; ++i) {
    InterfaceImplementation* impl = &(self->implementations.elements[i]);
    if (impl->interface == interface) {
      *result = true;
      return Ring1_Result_Success;
    }
  }
  *result = false;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_ClassType_getParentClassType
  (
    Mkx_ClassType** result,
    Mkx_ClassType* self
  )
{
  if (Ring1_Unlikely(!result || !self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = MKX_CLASSTYPE(self->parent);
  return Ring1_Result_Success;
}
