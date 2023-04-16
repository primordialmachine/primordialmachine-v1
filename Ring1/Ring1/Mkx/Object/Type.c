// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/Type.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Type.internal.h"
#include "Mkx/Object/Types.internal.h"
#undef MKX_OBJECT_INTERNAL


#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/ArrayType.internal.h"
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/InterfaceType.internal.h"
#include "Mkx/Object/ScalarType.internal.h"
#undef MKX_OBJECT_INTERNAL


#include "Ring1/Status.h"
#include <string.h>
#include <malloc.h>


int
Mkx_Type_construct
  (
    Mkx_Type *self,
    const char *name,
    void (*notifyTypeRemoved)(),
    int flags
  )
{
  if (Ring1_Unlikely(!self || !name)) {
    return 1;
  }
  if (Ring1_Unlikely(Ring1_Atom_getOrCreate(&self->name, name, strlen(name)))) {
    return 1;
  }
  self->flags = flags;
  self->notifyTypeRemoved = notifyTypeRemoved;
  return 0;
}

void
Mkx_Type_destruct
  (
    Mkx_Type* self
  )
{
  Ring1_Atom_unreference(self->name);
  self->name = NULL;
}

Ring1_CheckReturn() bool
Mkx_Type_isSubTypeOf
  (
    const Mkx_Type* a,
    const Mkx_Type* b
  )
{
  if (a == b)
  { return true; }
  
  int kind[2];
  if (Ring1_Unlikely(getTypeKind(&kind[0], a) || getTypeKind(&kind[1], b)))
  {
    /// @todo Proper error handling.
    /// @todo Use procedure style.
    return false;
  }

  // A scalar type is a subtype of another type only if they are the same type.
  if (Mkx_Type_Flags_ScalarType == kind[0] || Mkx_Type_Flags_ScalarType == kind[1])
  { return false; }

  /// @todo Use procedure style.
  if (Mkx_Type_Flags_ClassType == kind[0] && Mkx_Type_Flags_ClassType == kind[1])
  {
    const Mkx_Type* c = a;
    while (c)
    {
      if (c == b) return true;
      c = MKX_CLASSTYPE(c)->parent;
    }
  }
  return false;
}

Ring1_CheckReturn() int
Mkx_Type_isArrayType
  (
    bool* result,
    const Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!result || !type)) return 1;
  *result = (Mkx_Type_Flags_ArrayType == (type->flags & Mkx_Type_Flags_ArrayType));
  return 0;
}

Ring1_CheckReturn() int
Mkx_Type_isClassType
  (
    bool* result,
    const Mkx_Type *type
  )
{
  if (Ring1_Unlikely(!result || !type)) return 1;
  *result = (Mkx_Type_Flags_ClassType == (type->flags & Mkx_Type_Flags_ClassType));
  return 0;
}

Ring1_CheckReturn() int
Mkx_Type_isEnumerationType
  (
    bool* result,
    const Mkx_Type* type
  )
{ 
  if (Ring1_Unlikely(!result || !type)) return 1;
  *result = (Mkx_Type_Flags_EnumerationType == (type->flags & Mkx_Type_Flags_EnumerationType));
  return 0;
}

Ring1_CheckReturn() int
Mkx_Type_isInterfaceType
  (
    bool *result,
    const Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!result || !type)) return 1;
  *result = (Mkx_Type_Flags_InterfaceType == (type->flags & Mkx_Type_Flags_InterfaceType));
  return 0;
}

Ring1_CheckReturn() int
Mkx_Type_isScalarType
  (
    bool *result,
    const Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!result || !type)) return 1;
  *result = (Mkx_Type_Flags_ScalarType == (type->flags & Mkx_Type_Flags_ScalarType));
  return 0;
}

Ring1_CheckReturn() int
Mkx_Type_isInstantiableType
  (
    bool *result,
    const Mkx_Type* type
  ) 
{ 
  if (Ring1_Unlikely(!result || !type)) return 1;
  *result = (Mkx_Type_Flag_InstantiableType == (type->flags & Mkx_Type_Flag_InstantiableType));
  return 0;
}

Ring1_CheckReturn() int
Mkx_Type_getName
  (
    Ring1_Atom** result,
    const Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!result || !type)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_Atom_reference(type->name);
  *result = type->name;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() bool
Mkx_Type_isTrueSubTypeOf
  (
    const Mkx_Type* a,
    const Mkx_Type* b
  )
{
  if (a == b)
  { return false; }
  
  int kind[2];

  /// @todo Use procedure style.
  if (Ring1_Unlikely(getTypeKind(&kind[0], a) || getTypeKind(&kind[1], b)))
  { return false; }

  // A scalar type can never be a true subtype of a type.
  if (Mkx_Type_Flags_ScalarType == kind[0] || Mkx_Type_Flags_ScalarType == kind[1])
  { return false; }

  if (Mkx_Type_Flags_ClassType == kind[0] && Mkx_Type_Flags_ClassType == kind[1])
  {
    const Mkx_Type* c = a;
    while (c)
    {
      if (c == a && c != b) return true;
      c = MKX_CLASSTYPE(c)->parent;
    }
  }
  return false;
}

static int
hasDescendantsPredicate
  (
    bool* result,
    void* context,
    Mkx_Type* type
  )
{
  bool isClassType;
  if (Ring1_Unlikely(Mkx_Type_isClassType(&isClassType, type)))
  { return 1; }
 
  *result = false;
  
  if (isClassType)
  {
    if (MKX_CLASSTYPE(type)->parent == context)
    { *result = true; }
  }

  return 0;
}

int
Mkx_Type_hasDescendants
  (
    bool *result,
    Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!result || !type))
  { return 1; }
  if (Mkx_Type_Flags_ClassType == (type->flags & Mkx_Type_Flags_ClassType))
  {
    Mkx_Type* other;
    if (Ring1_Unlikely(Mkx_Object_Types_findFirst(&other, type, &hasDescendantsPredicate)))
    { return 1; }
    *result = (NULL != other);
  }
  else
  {
    *result = false;
  }
  return 0;
}
