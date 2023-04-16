#include "Ring1/Object/Test/WeakReferenceTests.h"
#include "Ring1/Object/Test/Data/MyTestObject.h"

/// @brief Test case: Get hard ref from valid weak ref.
/// @param ctx The test context.
/// @return #Ring1_Status_Success on success, a non-zero status code on failure.
Ring1_CheckReturn() static Ring1_Status
test1
  (
    Ring1_Test_Context *ctx
  )
{
  Ring1_Status s = Ring1_Status_Success;
  Ring1_ObjectModule_ModuleHandle h = Ring1_ModuleHandle_Invalid;
  Mkx_Object_Test_MyTestObject* o = NULL;
  Mkx_Object_Test_MyTestObject* o1 = NULL;
  Mkx_WeakReference* wr = NULL;

  h = Ring1_ObjectModule_ModuleHandle_acquire();
  RING1_TEST_ASSERT_NEQ(ctx, Ring1_ObjectModule_ModuleHandle_Invalid, h);
  if (!h) {
    s = 1; goto End;
  }

  s = Mkx_Object_Test_MyTestObject_createDefault(&o);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_Success, s);
  if (s) goto End;

  s = Mkx_WeakReference_create(&wr, MKX_OBJECT(o));
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_Success, s);
  if (s) goto End;

  s = Mkx_WeakReference_get((Mkx_Object**)&o1, wr);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_Success, s);
  if (s) goto End;
  RING1_TEST_ASSERT_EQ(ctx, o, o1);

End:
  if (o1) {
    Mkx_Object_unreference(MKX_OBJECT(o1));
    o1 = NULL;
  }
  if (wr) {
    Mkx_Object_unreference(MKX_OBJECT(wr));
    wr = NULL;
  }
  if (o) {
    Mkx_Object_unreference(MKX_OBJECT(o));
    o = NULL;
  }
  if (h) {
    Ring1_ObjectModule_ModuleHandle_relinquish(h);
    h = Ring1_ObjectModule_ModuleHandle_Invalid;
  }
  return s;
}

/// @brief Test case: Get hard ref from invalid weak ref.
/// @param ctx The test context.
/// @return #Ring1_Status_Success on success, a non-zero status code on failure.
Ring1_CheckReturn() static Ring1_Status
test2
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_Status s = Ring1_Status_Success;
  Ring1_ObjectModule_ModuleHandle h = Ring1_ModuleHandle_Invalid;
  Mkx_Object_Test_MyTestObject* o = NULL;
  Mkx_Object_Test_MyTestObject* o1 = NULL;
  Mkx_WeakReference* wr = NULL;

  h = Ring1_ObjectModule_ModuleHandle_acquire();
  RING1_TEST_ASSERT_NEQ(ctx, Ring1_ObjectModule_ModuleHandle_Invalid, h);
  if (!h) {
    s = 1; goto End;
  }
  s = Mkx_Object_Test_MyTestObject_createDefault(&o);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_Success, s);
  if (s) goto End;

  s = Mkx_WeakReference_create(&wr, MKX_OBJECT(o));
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_Success, s);
  if (s) goto End;

  Mkx_Object_unreference(MKX_OBJECT(o));
  o = NULL;

  s = Mkx_WeakReference_get((Mkx_Object **)&o1, wr);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_Success, s);
  if (s) goto End;
  RING1_TEST_ASSERT_EQ(ctx, NULL, o1);

End:
  if (o1) {
    Mkx_Object_unreference(MKX_OBJECT(o1));
    o1 = NULL;
  }
  if (wr) {
    Mkx_Object_unreference(MKX_OBJECT(wr));
    wr = NULL;
  }
  if (o) {
    Mkx_Object_unreference(MKX_OBJECT(o));
    o = NULL;
  }
  if (h) {
    Ring1_ObjectModule_ModuleHandle_relinquish(h);
    h = Ring1_ObjectModule_ModuleHandle_Invalid;
  }
  return s;
}

Ring1_CheckReturn() Ring1_Status
Mkx_Object_Test_WeakReferenceTests_register
  (
    Ring1_Test_Context* ctx
  )
{
  if (!ctx) return Ring1_Status_InvalidArgument;
  Ring1_Status status;

  status = Ring1_Test_Context_addTest(ctx, "Mkx.Object.Test.WeakReferenceTest | test 1", &test1);
  if (status) return status;
  status = Ring1_Test_Context_addTest(ctx, "Mkx.Object.Test.WeakReferenceTest | test 2", &test2);
  if (status) return status;

  return Ring1_Status_Success;
}
