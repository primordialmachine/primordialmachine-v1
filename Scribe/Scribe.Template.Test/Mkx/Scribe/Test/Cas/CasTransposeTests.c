#include "Mkx/Scribe/Test/Cas/CasTransposeTests.h"


#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


/// @brief Assert matrix transpose of a \f$2 \times 3\f$ matrix \f$M\f$ yields the correct results.
/// @example
/// The transpose of the matrix
/// \left(\begin{matrix}
/// a, b, c
/// d, e, f
/// \end{matrix}\right)
/// is computed as follows:
/// * \f$a\f$ is at \f$0,0\f$ and remains at \f$0,0\f$.
/// * \f$b\f$ is at \f$0,1\f$ and is moved to \f$1,0\f$.
/// * \f$c\f$ is at \f$0,2\f$ and is moved to \f$2,0\f$.
/// * \f$d\f$ is at \f$1,0\f$ and is moved to \f$0,1\f$.
/// * \f$e\f$ is at \f$1,1\f$ and remains at \f$1,1\f$.
/// * \f$f\f$ is at \f$1,2\f$ and is moved to \f$2,1\f4.
/// Hence the transpose of the matrix is
/// \begin{matrix}
/// a & d \\
/// b & e \\
/// c & f
/// \end{matrix}
TestBegin
  (
    transpose_2x3,
    "transpose"
    "("
    "matrix"
    "((v[0], v[1], v[2]),"
    " (v[3], v[4], v[5]))"
    ")",
    "matrix"
    "((v[0], v[3]),"
    " (v[1], v[4]),"
    " (v[2], v[5]))"
  )
{
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix1d(context, 2, 3, Mkx_Interpreter_Ffi_String_create(context, "v")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_TransposeNode_create(context, unevaluatedNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

/// @brief Assert matrix transpose of a \f$3 \times 2\f$ matrix \f$M\f$ yields the correct results.
/// @example
/// The transpose of the matrix
/// \left(\begin{matrix}
/// a, b
/// c, d
/// e, f
/// \end{matrix}\right)
/// is computed as follows:
/// * \f$a\f$ is at \f$0,0\f$ and remains at \f$0,0\f$.
/// * \f$b\f$ is at \f$0,1\f$ and is moved to \f$1,0\f$.
/// * \f$c\f$ is at \f$1,0\f$ and is moved to \f$0,1\f$.
/// * \f$d\f$ is at \f$1,1\f$ and remains at \f$1,1\f$.
/// * \f$e\f$ is at \f$2,0\f$ and is moved to \f$0,2\f$.
/// * \f$f\f$ is at \f$2,1\f$ and is moved to \f$1,2\f4.
/// Hence the transpose of the matrix is
/// \begin{matrix}
/// a & c & e \\
/// b & d & f \\
/// \end{matrix}
TestBegin
  (
    transpose_3x2,
    "transpose"
    "("
    "matrix"
    "((v[0], v[1]),"
    " (v[2], v[3]),"
    " (v[4], v[5]))"
    ")",
    "matrix"
    "((v[0], v[2], v[4]),"
    " (v[1], v[3], v[5]))"
  )
{
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_createMatrix1d(context, 3, 2, Mkx_Interpreter_Ffi_String_create(context, "v")));
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_TransposeNode_create(context, unevaluatedNode));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &transpose_2x3));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &transpose_3x2));
  Mkx_Interpreter_Context_destroy(context);
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerTransposeTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.TransposeTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
