#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Types.internal.h"

#include "Mkx/Object/Utilities/error.h"
#include "Mkx/Object/ArrayType.internal.h"
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/EnumerationType.internal.h"
#include "Mkx/Object/InterfaceType.internal.h"
#include "Mkx/Object/ScalarType.internal.h"
#include "Mkx/Object/Type.internal.h"

#undef MKX_OBJECT_INTERNAL


#include "Ring1/Memory/_Include.h" /// @todo Move into "Mkx/Object/Common.internal.h".


static Mkx_Type* g_types = NULL;


int
Mkx_Object_Types_add
  (
    Mkx_Type *type
  )
{
  type->next = g_types;
  g_types = type;
  return 0;
}

Ring1_CheckReturn() int
Mkx_Object_Types_initialize
  (
  )
{
  g_types = NULL;
  return 0;
}

int
Mkx_Object_Types_findFirst
  (
    Mkx_Type** result,
    void* context,
    int (*predicate)(bool *,void*, Mkx_Type*)
  )
{  
  Mkx_Type* current = g_types;
  while (current)
  {
    bool accepted = false;
    if ((*predicate)(&accepted, context, current))
    { return 1; }
    if (accepted)
    {
      *result = current;
      return 0;
    }
    current = current->next;
  }
  *result = NULL;
  return 0;
}

static void
destroyType
  (
    Mkx_Type* type
  )
{
  int kind;
  if (Ring1_Unlikely(getTypeKind(&kind, type)))
  {
    error_f("%s:%d: error: <internal error>\n", __FILE__, __LINE__);
    return;
  }
  switch (kind)
  {
  case Mkx_Type_Flags_ArrayType:
  {
    Mkx_ArrayType_destruct(MKX_ARRAYTYPE(type));
  }
  break;
  case Mkx_Type_Flags_ClassType:
  {
    Mkx_ClassType_destruct(MKX_CLASSTYPE(type));
  }
  break;
  case Mkx_Type_Flags_EnumerationType:
  {
    Mkx_EnumerationType_destruct(MKX_ENUMERATIONTYPE(type));
  }
  break;
  case Mkx_Type_Flags_InterfaceType:
  {
    Mkx_InterfaceType_destruct(MKX_INTERFACETYPE(type));
  } break;
  case Mkx_Type_Flags_ScalarType:
  {
    Mkx_ScalarType_destruct(MKX_SCALARTYPE(type));
  }
  break;
  default:
  {
    error_f("%s:%d: error: <internal error>\n", __FILE__, __LINE__);
    return;
  }
  };

  Ring1_Memory_deallocate(type);
}

/// Callback which determines if
/// - a type @a b is a user of a type @a a, and
/// - a != b.
int
Mkx_Object_Types_findFirstUserCallback
  (
    bool* result,
    const Mkx_Type* a,
    const Mkx_Type* b
  )
{ return b != a && Mkx_Type_isUserOf(result, b, a); }

/// Callback which determines if
/// - a type @a b is a user of a type @a a,
/// - a != b, and
/// - @a b is initialized.
int
Mkx_Object_Types_findFirstInitializedUserCallback
  (
    bool* result,
    const Mkx_Type* a,
    const Mkx_Type* b
  )
{ return b != a && Mkx_Type_isInitialized(b) && Mkx_Type_isUserOf(result, b, a); }

/// A leaf in the context of this function is any initialized type without initialized subtypes.
/// Until there are no more leaves:
/// Pick a leave and uninitialize it.
static void
uninitializeStep1
  (
  )
{
  // Uninitialize all types.
  bool done;
  do
  {
    done = true;
    for (Mkx_Type* type = g_types; type; type = type->next)
    {
      if (Mkx_Type_isInitialized(type))
      {
        Mkx_Type* firstInitializedUser;
        Mkx_Object_Types_findFirst(&firstInitializedUser, type, &Mkx_Object_Types_findFirstInitializedUserCallback);
        if (!firstInitializedUser)
        {
          Mkx_Type_ensureUninitialized(type);
          done = false;
        }
      }
    }
  } while (!done);

#if _DEBUG
  for (Mkx_Type* type = g_types; type; type = type->next)
  {
    if (Mkx_Type_isInitialized(type))
    {
      char* p; int64_t n;
      if (Ring1_Unlikely(!Ring1_Atom_getBytes(&p, type->name) &&
                         !Ring1_Atom_getNumberOfBytes(&n, type->name)))
      error_f("%s:%d: error: type `%.*s` not uninitialized\n", __FILE__, __LINE__, (int)n, p);
    }
  }
#endif
}

static void
uninitializeStep2
  (
  )
{
  bool done = true;
  while (g_types)
  {
    Mkx_Type** previous = &g_types,
      * current = g_types;
    while (current)
    {
      Mkx_Type* firstUser;
      Mkx_Object_Types_findFirst(&firstUser, current, &Mkx_Object_Types_findFirstUserCallback);
      if (!firstUser)
      {
        Mkx_Type* o = current;
        *previous = current->next;
        current = current->next;
        if (o->notifyTypeRemoved) o->notifyTypeRemoved();
        destroyType(o);
      }
      else
      {
        previous = &current->next;
        current = current->next;
      }
    }
  }
}

/// @brief Uninitialize and remove types.
/// @remark Invokes uninitializeStep1() and uninitializeStep2() in that order.
void
Mkx_Object_Types_uninitialize
  (
  )
{
  uninitializeStep1();
  uninitializeStep2();
  if (g_types)
  {
    error_f("%s:%d: error: type pruning inomcplete\n", __FILE__, __LINE__);
  }
}
