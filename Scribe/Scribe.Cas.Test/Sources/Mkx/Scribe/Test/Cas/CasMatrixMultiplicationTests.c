#include "Mkx/Scribe/Test/Cas/CasMatrixSubtractionTests.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


TestBegin
  (
    matrixMultiplication_1x1_1x1,
    "matrix"
    "("
      "(a[0,0])"
    ")"
    " * "
    "matrix"
    "("
      "(b[0,0])"
    ")",
    "matrix"
    "("
      "(a[0,0] * b[0,0])"
    ")"
  )
{
  Mkx_Scribe_Cas_Node* leftOperand = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(1, 1, Ring2_String_fromC(false, "a")));
  Mkx_Scribe_Cas_Node* rightOperand = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(1, 1, Ring2_String_fromC(false, "b")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(leftOperand, rightOperand));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

TestBegin
  (
    matrixMultiplication_2x2_2x2,
    "matrix"
    "("
      "(a[0,0], a[0,1]), "
      "(a[1,0], a[1,1])"
    ")"
    " * "
    "matrix"
    "("
      "(b[0,0], b[0,1]), "
      "(b[1,0], b[1,1])"
    ")",
    "matrix"
    "("
      "(a[0,0] * b[0,0] + a[0,1] * b[1,0], a[0,0] * b[0,1] + a[0,1] * b[1,1]), "
      "(a[1,0] * b[0,0] + a[1,1] * b[1,0], a[1,0] * b[0,1] + a[1,1] * b[1,1])"
    ")"
  )
{
  Mkx_Scribe_Cas_Node* leftOperand = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(2, 2, Ring2_String_fromC(false, "a")));
  Mkx_Scribe_Cas_Node* rightOperand = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(2, 2, Ring2_String_fromC(false, "b")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(leftOperand, rightOperand));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixMultiplication_1x1_1x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixMultiplication_2x2_2x2));
  Ring2_Context_shutdown();
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerMatrixMultiplicationTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.MatrixMultiplicationTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
