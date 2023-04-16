#include "Ring1/Object/Test/Data/MyTestObject.h"

Ring1_NonNull() static void
Mkx_Object_Test_MyTestObject_destruct
  (
    Mkx_Object_Test_MyTestObject *self
  )
{}

Mkx_Type_DefineClassType("Mkx.Object.Test.MyTestObject", Mkx_Object_Test_MyTestObject, MKX_OBJECT_TEST_MYTESTOBJECT,
                         Mkx_Object,
                         Mkx_Type_UseDefaultMemoryManager(),
                         Mkx_Type_ImplementInterfaces())


Ring1_CheckReturn() static Ring1_Status
Mkx_Object_Test_MyTestObject_Dispatch_construct
  (
    Mkx_Object_Test_MyTestObject_Dispatch* self
  )
{ return Ring1_Status_Success; }

static void
Mkx_Object_Test_MyTestObject_Dispatch_destruct
  (
    Mkx_Object_Test_MyTestObject_Dispatch* self
  )
{}

Ring1_CheckReturn() Ring1_Status
Mkx_Object_Test_MyTestObject_constructDefault
  (
    Mkx_Object_Test_MyTestObject *self
  )
{
  Mkx_Type* type = MKX_TYPE_GET(Mkx_Object_Test_MyTestObject);
  if (Ring1_Unlikely(!type)) return 1;
  if (Ring1_Unlikely(Mkx_Object_construct(MKX_OBJECT(self)))) return 1;
  MKX_OBJECT(self)->type = type;
  return Ring1_Status_Success;
}

MKX_DEFAULTCREATORDEFINITION(Mkx_Object_Test_MyTestObject)
