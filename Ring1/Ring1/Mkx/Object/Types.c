// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/Types.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Types.h"
#include "Mkx/Object/Types.internal.h"

#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/EnumerationType.internal.h"
#include "Mkx/Object/InterfaceType.internal.h"
#include "Mkx/Object/ScalarType.internal.h"
#include "Mkx/Object/Type.internal.h"

#undef MKX_OBJECT_INTERNAL


#include "Ring1/Memory/_Include.h"
#include <string.h>


static int
findByNamePredicate
  (
    bool* result,
    void* context,
    Mkx_Type* type
  )
{
  char* p;
  int64_t n;
  if (Ring1_Unlikely(Ring1_Atom_getBytes(&p, type->name) || Ring1_Atom_getNumberOfBytes(&n, type->name)))
  { return 1; }
  const char* q = (const char*)context;
  size_t ql = strlen(q);
  if (ql != n)
  {
    *result = false;
  }
  else
  {
    *result = !strncmp(q, p, ql);
  }
  return 0;
}

static int
findByName
  (
    Mkx_Type **result,
    const char *name
  )
{
  if (!name) return 1;
  return Mkx_Object_Types_findFirst(result, (void *)name, &findByNamePredicate);
}

Mkx_Type*
Mkx_registerClassType
  (
    void (*notifyTypeRemoved)(),
    const Mkx_ClassTypeRegistrationInfo *info
  )
{
  Mkx_Type* current;

  //
  if (!info || !info->name) return NULL;
  
  //
  if (findByName(&current, info->name)) return NULL;
  if (current) return NULL;
  
  //
  if (Ring1_Memory_allocate(&current, sizeof(Mkx_ClassType))) return NULL;
  if (Mkx_ClassType_construct(MKX_CLASSTYPE(current), notifyTypeRemoved, info))
  {
    Ring1_Memory_deallocate(current);
    return NULL;
  }

  //
  if (Mkx_Object_Types_add(current))
  {
    Mkx_ClassType_destruct(MKX_CLASSTYPE(current));
    Ring1_Memory_deallocate(current);
    return NULL;    
  }

  //
  return current;
}

Mkx_Type*
Mkx_registerEnumerationType
  (
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  )
{
  Mkx_Type* current;

  //
  if (!name) return NULL;

  //
  if (findByName(&current, name)) return NULL;
  if (current) return NULL;

  //
  if (Ring1_Memory_allocate(&current, sizeof(Mkx_ScalarType))) return NULL;
  if (Mkx_EnumerationType_construct(MKX_ENUMERATIONTYPE(current), name, notifyTypeRemoved, size))
  {
    Ring1_Memory_deallocate(current);
    return NULL;
  }

  //
  if (Mkx_Object_Types_add(current))
  {
    Mkx_EnumerationType_destruct(MKX_ENUMERATIONTYPE(current));
    Ring1_Memory_deallocate(current);
    return NULL;    
  }

  //
  return current;
}

Mkx_Type*
Mkx_registerInterfaceType
  (
    const char* name,
    void (*notifyTypeRemoved)(),
    int (*addPrerequisites)(Mkx_InterfaceType *self),
    size_t dispatchSize
  )
{
  Mkx_Type* current;

  //
  if (!name) return NULL;

  //
  if (findByName(&current, name)) return NULL;
  if (current) return NULL;

  //
  if (Ring1_Memory_allocate(&current, sizeof(Mkx_InterfaceType))) return NULL;
  if (Mkx_InterfaceType_construct(MKX_INTERFACETYPE(current), name, notifyTypeRemoved, addPrerequisites, dispatchSize))
  {
    Ring1_Memory_deallocate(current);
    return NULL;
  }

  //
  if (Mkx_Object_Types_add(current))
  {
    Mkx_InterfaceType_destruct(MKX_INTERFACETYPE(current));
    Ring1_Memory_deallocate(current);
    return NULL;    
  }

  //
  return current;
}

Mkx_Type*
Mkx_registerScalarType
  (
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  )
{
  Mkx_Type* current;

  //
  if (!name) return NULL;

  //
  if (findByName(&current, name)) return NULL;
  if (current) return NULL;

  //
  if (Ring1_Memory_allocate(&current, sizeof(Mkx_ScalarType))) return NULL;
  if (Mkx_ScalarType_construct(MKX_SCALARTYPE(current), name, notifyTypeRemoved, size))
  {
    Ring1_Memory_deallocate(current);
    return NULL;
  }

  //
  if (Mkx_Object_Types_add(current))
  {
    Mkx_ScalarType_destruct(MKX_SCALARTYPE(current));
    Ring1_Memory_deallocate(current);
    return NULL;    
  }

  //
  return current;
}
