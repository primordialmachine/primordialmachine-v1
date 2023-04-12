#include "Mkx/Scribe/Test/Cas/CasMatrixSubtractionTests.h"


#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


TestBegin
  (
    matrixSubtraction_1x1,
    "matrix"
    "("
      "(a[0,0])"
    ")"
    " - "
    "matrix"
    "("
      "(b[0,0])"
    ")",
    "matrix"
    "("
      "(a[0,0] - b[0,0])"
    ")"
  )
{
  Mkx_Scribe_Cas_Node* leftOperand = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 1, 1, Mkx_Interpreter_Ffi_String_create(context, "a")));
  Mkx_Scribe_Cas_Node* rightOperand = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 1, 1, Mkx_Interpreter_Ffi_String_create(context, "b")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(context, leftOperand, rightOperand));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

TestBegin
(
  matrixSubtraction_2x2,
  "matrix"
  "("
    "(a[0,0], a[0,1]), "
    "(a[1,0], a[1,1])"
  ")"
  " - "
  "matrix"
  "("
    "(b[0,0], b[0,1]), "
    "(b[1,0], b[1,1])"
  ")",
  "matrix"
  "("
    "(a[0,0] - b[0,0], a[0,1] - b[0,1]), "
    "(a[1,0] - b[1,0], a[1,1] - b[1,1])"
  ")"
)
{
  Mkx_Scribe_Cas_Node* leftOperand = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 2, 2, Mkx_Interpreter_Ffi_String_create(context, "a")));
  Mkx_Scribe_Cas_Node* rightOperand = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 2, 2, Mkx_Interpreter_Ffi_String_create(context, "b")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(context, leftOperand, rightOperand));
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
  {
    return;
  }
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &matrixSubtraction_1x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &matrixSubtraction_2x2));
  Mkx_Interpreter_Context_destroy(context);
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerMatrixSubtractionTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.MatrixSubtractionTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
