#if !defined(MKX_OBJECT_TEST_MYTESTOBJECT_H_INCLUDED)
#define MKX_OBJECT_TEST_MYTESTOBJECT_H_INCLUDED

#include "Mkx/Object.h"


Mkx_Type_DeclareClassType("Mkx.Object.Test.MyTestObject", Mkx_Object_Test_MyTestObject, MKX_OBJECT_TEST_MYTESTOBJECT)

struct Mkx_Object_Test_MyTestObject_Dispatch
{
  Mkx_Object_Dispatch parent;
};

struct Mkx_Object_Test_MyTestObject
{
  Mkx_Object parent;
};

MKX_DEFAULTCONSTRUCTORDECLARATION(Mkx_Object_Test_MyTestObject)
MKX_DEFAULTCREATORDECLARATION(Mkx_Object_Test_MyTestObject)


#endif // MKX_OBJECT_TEST_MYTESTOBJECT_H_INCLUDED
