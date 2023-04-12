#include "Mkx/Scribe/Test/Cas/CasDeterminantTests.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


/// @brief Assert determinant of a \f$0 \times 0\f$ matrix \f$M\f$ yields the correct results.
TestBegin
  (
    matrixDeterminant_0x0,
    "determinant(matrix())",
    "1"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(0, 0, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeterminantNode_create(matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

/// @brief Assert determinant of a \f$1 \times 1\f$ matrix \f$M\f$ yields the correct results.
TestBegin
  (
    matrixDeterminant_1x1,
    "determinant(matrix((v[0,0])))",
    "v[0,0]"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(1, 1, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeterminantNode_create(matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert determinant of a \f$2 \times 2\f$ matrix yields the correct results.
TestBegin
  (
    matrixDeterminant_2x2,
    "determinant(matrix((v[0,0], v[0,1]), (v[1,0], v[1,1])))",
    "v[0,0] * v[1,1] - v[0,1] * v[1,0]"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(2, 2, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeterminantNode_create(matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

/// @brief Assert determinant of a \f$3 \times 3\f$ matrix yields correct results.
/// @todo The outcommented result string is the desired result string. Fix optimizer to produce that string.
TestBegin
  (
    matrixDeterminant_3x3,
    "determinant(matrix((v[0,0], v[0,1], v[0,2]), (v[1,0], v[1,1], v[1,2]), (v[2,0], v[2,1], v[2,2])))",
    "v[0,0] * (v[1,1] * v[2,2] - v[1,2] * v[2,1]) + v[0,1] * -(v[1,0] * v[2,2] - v[1,2] * v[2,0]) + v[0,2] * (v[1,0] * v[2,1] - v[1,1] * v[2,0])"
    //"v[0,0] * (v[1,1] * v[2,2] - v[1,2] * v[2,1]) - v[0,1] * (v[1,0] * v[2,2] - v[1,2] * v[2,0]) + v[0,2] * (v[1,0] * v[2,1] - v[1,1] * v[2,0])"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(3, 3, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_DeterminantNode_create(matrixNode));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixDeterminant_0x0));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixDeterminant_1x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixDeterminant_2x2));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixDeterminant_3x3));
  Ring2_Context_shutdown();
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerDeterminantTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.DeterminantTest", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
