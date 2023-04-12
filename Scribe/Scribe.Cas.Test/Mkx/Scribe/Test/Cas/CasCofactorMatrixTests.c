#include "Mkx/Scribe/Test/Cas/CasAdjugateTests.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


/// @brief Assert the cofactor matrix of a \f$1 \times 1\f$ matrix \f$M\f$ yields correct results.
/// @detail
/// Compute the cofactors of the elements:
/// * The cofactor of row 0 and column 0 is \f$1\f$.
/// Hence the cofactor matrix is
/// \[
/// \begin{matrix}
/// 1
/// \end{matrix}
/// \]
TestBegin
  (
    cofactorMatrix_1x1,
    "cofactorMatrix"
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
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(1, 1, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_CofactorMatrixNode_create(matrixNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

/// @brief Assert the cofactor matrix of a \f$2 \times f2\f$ matrix \f$M\f$ yields correct results.
/// @detail
/// Compute the cofactorrs of the elements:
/// * The cofactor of row 0 and column 0 is \f$m_{1,1}\f$.
/// * The cofactor of row 0 and column 1 is \f$-m_{1,0}\f$.
/// * The cofactor of row 1 and column 0 is \f$-m_{0,1}\f$.
/// * The cofactor of row 1 and column 1 is \f$m_{0,0}\f$.
/// Hence the cofactor matrix is
/// \[
/// \begin{matrix}
///  m_{1,1} & -m_{1,0}\\
/// -m_{0,1} &  m_{0,0}
/// \end{matrix}
/// \]
TestBegin
  (
    cofactorMatrix_2x2,
    "cofactorMatrix"
    "("
      "matrix"
      "("
        "(v[0,0], v[0,1]), "
        "(v[1,0], v[1,1])"
      ")"
    ")",
    "matrix"
    "("
      "(v[1,1], -v[1,0]), "
      "(-v[0,1], v[0,0])"
    ")"
  )
{
  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(2, 2, Ring2_String_fromC(false, "v")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_CofactorMatrixNode_create(matrixNode));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&cofactorMatrix_1x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&cofactorMatrix_2x2));
  Ring2_Context_shutdown();
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerCofactorMatrixTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.CofactorMatrixTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
