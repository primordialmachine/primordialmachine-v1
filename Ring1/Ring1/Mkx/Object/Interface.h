#if !defined(RING1_OBJECT_INTERFACE_H_INCLUDED)
#define RING1_OBJECT_INTERFACE_H_INCLUDED

#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/Interface.h' directly, include 'Mkx/Object.h' instead.")
#endif

#include "Mkx/Object/Type.h"
#include "Mkx/Object/Dispatch.h"


#define MKX_INTERFACE(pointer) ((Mkx_Interface *)(pointer))
typedef struct Mkx_Interface Mkx_Interface;

struct Mkx_Interface
{
  Mkx_Type* type;
};

#define MKX_INTERFACE_DISPATCH(pointer) ((Mkx_Interface_Dispatch *)(pointer))
typedef struct Mkx_Interface_Dispatch Mkx_Interface_Dispatch;

struct Mkx_Interface_Dispatch
{
  Mkx_Dispatch parent;
};

Mkx_Type *
__Mkx_Interface_getType__
  (
  );

#endif // RING1_OBJECT_INTERFACE_H_INCLUDED
