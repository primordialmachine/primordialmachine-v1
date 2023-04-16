#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Utilities/error.h"
#include "Mkx/Object/ArrayType.internal.h"
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/EnumerationType.internal.h"
#include "Mkx/Object/InterfaceType.internal.h"
#include "Mkx/Object/ScalarType.internal.h"
#include "Mkx/Object/Type.internal.h"
#undef MKX_OBJECT_INTERNAL


Ring1_CheckReturn() Ring1_NonNull() int
Mkx_Type_ensureInitialized
  (
    Mkx_Type* self
  )
{
  if (Ring1_Unlikely(!self)) return 1;
  if (0 == (self->flags & Mkx_Type_Flags_Initialized))
  {
    /// @todo Truly ensure the type is initialized.
    /// We need to do this
    /// - for interface types (addPrerequisites) and
    /// - for class types.
    bool isClassType;
    Mkx_Type_isClassType(&isClassType, self);
    if (isClassType)
    {
      if (Mkx_ClassType_ensureInitialized(MKX_CLASSTYPE(self)))
      {
        return 1;
      }
    }
    else if (Mkx_InterfaceType_ensureInitialized(MKX_INTERFACETYPE(self)))
    {
      if (Mkx_InterfaceType_ensureInitialized(MKX_INTERFACETYPE(self)))
      {
        return 1;
      }
    }
    else if (Mkx_ArrayType_ensureInitialized(MKX_ARRAYTYPE(self)))
    {
      if (Mkx_ArrayType_ensureInitialized(MKX_ARRAYTYPE(self)))
      {
        return 1;
      }
    }
    self->flags |= Mkx_Type_Flags_Initialized;
  }
  return 0;
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_Type_ensureUninitialized
  (
    Mkx_Type* self
  )
{
  if (Ring1_Unlikely(!self))
  { return 1; }
  if (Mkx_Type_Flags_Initialized == (self->flags & Mkx_Type_Flags_Initialized))
  {
    int kind;
    if (Ring1_Unlikely(getTypeKind(&kind, self)))
    { return 1; }
    if (Mkx_Type_Flags_ClassType == kind)
    {
      Mkx_ClassType_ensureUninitialized(MKX_CLASSTYPE(self));
    }
    else if (Mkx_Type_Flags_InterfaceType == kind)
    {
      Mkx_InterfaceType_ensureUninitialized(MKX_INTERFACETYPE(self));
    }
    else if (Mkx_Type_Flags_ArrayType == kind)
    {
      Mkx_ArrayType_ensureUninitialized(MKX_ARRAYTYPE(self));
    }
    MKX_TYPE(self)->flags = (MKX_TYPE(self)->flags & ~Mkx_Type_Flags_Initialized);
  }
  return 0;
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_Type_isUserOf
  (
    bool* result,
    const Mkx_Type* a,
    const Mkx_Type* b
  )
{
  int kinda;

  if (Ring1_Unlikely(getTypeKind(&kinda, a)))
  { return 1; }

  switch (kinda)
  {
  case Mkx_Type_Flags_ArrayType:
  {
    return Mkx_ArrayType_isUserOf(result, MKX_ARRAYTYPE(a), b);
  } break;
  case Mkx_Type_Flags_ClassType:
  {
    return Mkx_ClassType_isUserOf(result, MKX_CLASSTYPE(a), b);
  } break;
  case Mkx_Type_Flags_EnumerationType:
  {
    return Mkx_EnumerationType_isUserOf(result, MKX_ENUMERATIONTYPE(a), b);
  } break;
  case Mkx_Type_Flags_InterfaceType:
  {
    return Mkx_InterfaceType_isUserOf(result, MKX_INTERFACETYPE(a), b);
  } break;
  case Mkx_Type_Flags_ScalarType:
  {
    return Mkx_ScalarType_isUserOf(result, MKX_SCALARTYPE(a), b);
  } break;
  default:
  {
    error_f("%s:%d: error: <internal error>\n", __FILE__, __LINE__);
    return 1;
  } break;
  };
}
