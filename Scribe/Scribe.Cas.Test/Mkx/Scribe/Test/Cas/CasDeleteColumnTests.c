#include "Mkx/Scribe/Test/Cas/CasDeleteColumnTests.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


// Assert delete column works.
TestBegin
  (
    deleteColumn_3x1,
    "deleteColumn(0, matrix"
    "((v[0,0]), (v[1,0]), (v[2,0])))",
    "matrix"
    "((), (), ())"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(3, 1, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeleteColumnNode_create(0, matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()


// Assert delete column works.
TestBegin
  (
    deleteColumn_3x3,
    "deleteColumn(1, matrix"
    "((v[0,0], v[0,1], v[0,2]),"
    " (v[1,0], v[1,1], v[1,2]),"
    " (v[2,0], v[2,1], v[2,2])))",
    "matrix"
    "((v[0,0], v[0,2]),"
    " (v[1,0], v[1,2]),"
    " (v[2,0], v[2,2]))"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(3, 3, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeleteColumnNode_create(1, matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert delete column works.
TestBegin
  (
    deleteColumn_4x4,
    "deleteColumn(1, matrix"
    "((v[0,0], v[0,1], v[0,2], v[0,3]),"
    " (v[1,0], v[1,1], v[1,2], v[1,3]),"
    " (v[2,0], v[2,1], v[2,2], v[2,3]),"
    " (v[3,0], v[3,1], v[3,2], v[3,3])))",
    "matrix"
    "((v[0,0], v[0,2], v[0,3]),"
    " (v[1,0], v[1,2], v[1,3]),"
    " (v[2,0], v[2,2], v[2,3]),"
    " (v[3,0], v[3,2], v[3,3]))"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(4, 4, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeleteColumnNode_create(1, matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

static Ring1_Result
test
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_Result result;
  if (result = Ring2_Context_startup()) {
    RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
    return Ring1_Result_Failure;
  }
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&deleteColumn_3x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&deleteColumn_3x3));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&deleteColumn_4x4));
  Ring2_Context_shutdown();
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerDeleteColumnTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.DeleteColumnTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
