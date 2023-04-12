#include "Mkx/Scribe/Test/Cas/CasAdjugateTests.h"


#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


/// @brief Assert the cofactor matrix of a \f$1 \times 1\f$ matrix \f$M\f$ yields correct results.
/// @detail
/// The cofactor matrix is
/// \[
/// \begin{matrix}
/// 1
/// \end{matrix}
/// \]
/// Hence the adjugate is
/// \[
/// \begin{matrix}
/// 1
/// \end{matrix}
/// \]
TestBegin
  (
    adjugate_1x1,
    "adjugate"
    "("
      "matrix"
      "("
        "(v[0,0])"
      ")"
    ")",
    "matrix"
    "("
      "(1)"
    ")"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 1, 1, Mkx_Interpreter_Ffi_String_create(context, "v")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_AdjugateNode_create(context, matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

/// @brief Assert the cofactor matrix of a \f$2 \times f2\f$ matrix \f$M\f$ yields correct results.
/// @detail
/// The cofactor matrix is
/// \[
/// \begin{matrix}
/// m_{1,1} & -m_{1,0}\\
/// -m_{0,1} & m_{0,0}
/// \end{matrix}
/// \]
/// Hence the adjugate is
/// \[
/// \begin{matrix}
/// m_{1,1} & -m_{0,1}\\
/// -m_{1,0} & m_{0,0}
/// \end{matrix}
/// \]
TestBegin
  (
    adjugate_2x2,
    "adjugate"
    "("
      "matrix"
      "("
        "(v[0,0], v[0,1]), "
        "(v[1,0], v[1,1])"
      ")"
    ")",
    "matrix"
    "("
      "(v[1,1], -v[0,1]), "
      "(-v[1,0], v[0,0])"
    ")"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(context, 2, 2, Mkx_Interpreter_Ffi_String_create(context, "v")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_AdjugateNode_create(context, matrixNode));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &adjugate_1x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &adjugate_2x2));
  Mkx_Interpreter_Context_destroy(context);
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerAdjugateTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.AdjugateTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
