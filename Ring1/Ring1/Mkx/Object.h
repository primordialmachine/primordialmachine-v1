#if !defined(MKX_OBJECT_H_INCLUDED)
#define MKX_OBJECT_H_INCLUDED

#include "Ring1/Module.h"

#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/BoxedValue.h"
#include "Mkx/Object/Interface.h"
#include "Mkx/Object/Object.h"
#include "Mkx/Object/Type.h"
#include "Mkx/Object/TypeDeclaration.h"
#include "Mkx/Object/TypeDefinition.h"
#include "Mkx/Object/WeakReference.h"
#undef MKX_OBJECT_INTERNAL

/// @brief Function annotation indicating a class method (as opposed to an object method).
#define Mkx_ClassMethod()

Ring1_Module_Declare(Ring1, ObjectModule);

/// @brief Utiltiy macro to declare a default creator.
/// @param CNAME The C name of the type e.g. <code>Mkx_Scene_Viewport</code>.
#define Mkx_DeclareDefaultCreator(CNAME) \
  Ring1_CheckReturn() int \
  CNAME##_createDefault \
    ( \
      CNAME **result \
    );

/// @brief Utility macro to define a default creator.
/// @param CNAME The C name of the type e.g. <code>Mkx_Scene_Viewport</code>.
#define Mkx_DefineDefaultCreator(CNAME) \
  Ring1_CheckReturn() int \
  CNAME##_createDefault \
    ( \
      CNAME **result \
    ) \
  { \
    Mkx_Type* type = MKX_TYPE_GET(CNAME); \
    if (Ring1_Unlikely(!type)) return 1; \
    CNAME* self = Mkx_Object_allocate(type); \
    if (Ring1_Unlikely(!self)) return 1; \
    if (Ring1_Unlikely(CNAME##_constructDefault(self))) \
    { \
      Mkx_Object_unreference(MKX_OBJECT(self)); \
      return 1; \
    } \
    *result = self; \
    return 0; \
  }

#endif // MKX_OBJECT_H_INCLUDED
