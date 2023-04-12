#include "Mkx/Scribe/Test/Cas/CasDeleteRowTests.h"


#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


// Assert delete row works.
TestBegin
  (
    deleteRow_1x3,
    "deleteRow(0, matrix"
    "((v[0,0], v[0,1], v[0,2])))",
    "matrix"
    "()"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 1, 3, Mkx_Interpreter_Ffi_String_create(context, "v")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeleteRowNode_create(context, 0, matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert delete row works.
TestBegin
  (
    deleteRow_4x4,
    "deleteRow"
    "(1, "
    "matrix"
    "((v[0,0], v[0,1], v[0,2], v[0,3]),"
    " (v[1,0], v[1,1], v[1,2], v[1,3]),"
    " (v[2,0], v[2,1], v[2,2], v[2,3]),"
    " (v[3,0], v[3,1], v[3,2], v[3,3]))"
    ")",
    "matrix"
    "((v[0,0], v[0,1], v[0,2], v[0,3]),"
    " (v[2,0], v[2,1], v[2,2], v[2,3]),"
    " (v[3,0], v[3,1], v[3,2], v[3,3]))"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 4, 4, Mkx_Interpreter_Ffi_String_create(context, "v")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeleteRowNode_create(context, 1, matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

static void
test
  (
    Ring1_Test_Context* ctx
  )
{
  Mkx_Interpreter_Context* context = Mkx_Interpreter_Context_create();
  RING1_TEST_ASSERT_NOTNULL(ctx, context);
  if (!context)
  { return; }
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &deleteRow_1x3));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &deleteRow_4x4));
  Mkx_Interpreter_Context_destroy(context);
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerDeleteRowTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.DeleteRowTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
