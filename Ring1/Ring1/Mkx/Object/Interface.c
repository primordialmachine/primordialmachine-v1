#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Interface.h"
#include "Mkx/Object/Types.h"
#undef MKX_OBJECT_INTERNAL


static Mkx_Type* g_type = NULL;

static inline void
typeRemoved
  (
  )
{ g_type = NULL; }

Mkx_Type *
__Mkx_Interface_getType__
  (
  )
{
  if (!g_type)
  {
    g_type = Mkx_registerInterfaceType("Mkx.Interface", &typeRemoved, NULL, sizeof(Mkx_Interface_Dispatch));
  }
  return g_type;
}
