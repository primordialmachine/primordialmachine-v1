#include "Mkx/Scribe/Test/Cas/CasTests.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


// Assert "a" yields "a".
TestBegin(variable, "a", "a")
{
  Ring2_String* variableName = Ring2_String_fromC(false, "a");
  Mkx_Scribe_Cas_Node* variableNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VariableNode_create(variableName));
  unevaluatedNode = variableNode;
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "a[0]" yields "a[0]".
TestBegin(index1dVariable, "a[0]", "a[0]")
{
  Ring2_String* variableName = Ring2_String_fromC(false, "a");
  Mkx_Scribe_Cas_Node* variableNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VariableNode_create(variableName));
  Mkx_Scribe_Cas_Node* indexNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_Index1dNode_create(0, variableNode));
  unevaluatedNode = indexNode;
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "a[0,0]" yields "a[0,0]".
TestBegin(index2dVariable, "a[0,0]", "a[0,0]")
{
  Ring2_String* variableName = Ring2_String_fromC(false, "a");
  Mkx_Scribe_Cas_Node* variableNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VariableNode_create(variableName));
  Mkx_Scribe_Cas_Node* indexNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_Index2dNode_create(0, 0, variableNode));
  unevaluatedNode = indexNode;
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "(1)" yields "1".
TestBegin(oneInGroup, "(1)", "1")
{
  Mkx_Scribe_Cas_Node *oneNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(oneNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "(0)" yields "0".
TestBegin(zeroInGroup, "(0)", "0")
{
  Mkx_Scribe_Cas_Node* oneNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(oneNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "(x)" yields "x".
TestBegin(variableInGroup, "(x)", "x")
{
  Mkx_Scribe_Cas_Node* oneNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_VariableNode_create(Ring2_String_fromC(false, "x")));
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(oneNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert the \f$4 \times 4\f$ zero matrix is "matrix((0, 0, 0), (0, 0, 0), (0, 0, 0))".
TestBegin
  (
    zeroMatrix,
    "matrix((0, 0, 0), (0, 0, 0), (0, 0, 0))",
    "matrix((0, 0, 0), (0, 0, 0), (0, 0, 0))"
  )
{
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_MatrixNode_create(3, 3));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

/// @brief Assert the minors of a \f$1 \times 1\f$ matrix \f$M\f$ yield correct results.
/// @detail
/// * The minor of row 0 and column 0 is \f$1\f$.
static void
minor_1x1
  (
  )
{
  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(1, 1, Ring2_String_fromC(false, "v")));

  static const char* results[] =
  {
    "1"
  };

  int64_t k = 0;
  for (int64_t i = 0, n = 1; i < n; ++i)
  {
    for (int64_t j = 0, m = 1; j < m; ++j)
    {
      Mkx_Scribe_Cas_EmissionContext_reset(emissionContext);
      Mkx_Scribe_Cas_Node* cofactorNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_MinorNode_create(i, j, matrixNode));
      Mkx_Scribe_Cas_Node* evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, cofactorNode);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, evaluatedNode);
      Ring2_String* string = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s\n"), string);
      if (!Ring2_String_isEqualTo(Ring2_Context_get(), string, Ring2_String_fromC(false, results[k++])))
      {
        Ring1_Status_set(Ring1_Status_TestFailed);
        Ring2_jump();
      }
    }
  }
}

/// @brief Assert the minors of a \f$2 \times 2\f$ matrix \f$M\f$ yield correct results.
/// @detail
/// * cofactor of row 0 and column 0:
///   The minor of row 0 and column 0 is \f$det(\begin{matrix}m_{1,1}\end{matrix}) = m_{1,1}\f$.
/// * cofactor of row 0 and column 1:
///   The minor of row 0 and column 1 is \f$det(\begin{matrix}m_{1,0}\end{matrix}) = m_{1,0}\f$
/// * cofactor of row 1 and column 0:
///   The minor of row 1 and column 0 is \f$det(\begin{matrix}m_{0,1}\end{matrix}) = m_{0,1}\f$.
/// * cofactor of row 1 and column 1:
///   The minor of row 1 and column 1 is \f$det(\begin{matrix}m_{0,0}\end{matrix}) = m_{0,0}\f$.
static void
minor_2x2
  (
  )
{

  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(2, 2, Ring2_String_fromC(false, "v")));

  static const char* results[] =
  {
    "v[1,1]",
    "v[1,0]",
    "v[0,1]",
    "v[0,0]",
  };

  int64_t k = 0;
  for (int64_t i = 0, n = 2; i < n; ++i)
  {
    for (int64_t j = 0, m = 2; j < m; ++j)
    {
      Mkx_Scribe_Cas_EmissionContext_reset(emissionContext);
      Mkx_Scribe_Cas_Node* cofactorNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_MinorNode_create(i, j, matrixNode));
      Mkx_Scribe_Cas_Node* evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, cofactorNode);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, evaluatedNode);
      Ring2_String* string = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s\n"), string);
      if (!Ring2_String_isEqualTo(Ring2_Context_get(), string, Ring2_String_fromC(false, results[k++])))
      {
        Ring1_Status_set(Ring1_Status_TestFailed);
        Ring2_jump();
      }
    }
  }
}

/// @brief Assert cofactors \f$1 \times 1\f$ matrix \f$M\f$ yield correct results.
/// @detail
/// * cofactor of row 0 and column 0:
///   The minor of row 0 and column 0 is \f$1\f$.
///   Hence the cofactor is \f$(-1)^{0 + 0 + 2} 1 = 1\f$.
static void
cofactor_1x1
  (
  )
{

  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(1, 1, Ring2_String_fromC(false, "v")));

  static const char* results[] =
  {
    "1"
  };

  int64_t k = 0;
  for (int64_t i = 0, n = 1; i < n; ++i)
  {
    for (int64_t j = 0, m = 1; j < m; ++j)
    {
      Mkx_Scribe_Cas_EmissionContext_reset(emissionContext);
      Mkx_Scribe_Cas_Node* cofactorNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_CofactorNode_create(i, j, matrixNode));
      Mkx_Scribe_Cas_Node* evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, cofactorNode);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, evaluatedNode);
      Ring2_String* string = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s\n"), string);
      if (!Ring2_String_isEqualTo(Ring2_Context_get(), string, Ring2_String_fromC(false, results[k++])))
      {
        Ring1_Status_set(Ring1_Status_TestFailed);
        Ring2_jump();
      }
    }
  }
}

/// @brief Assert cofactors \f$2 \times 2\f$ matrix \f$M\f$ yield correct results.
/// @detail
/// * cofactor of row 0 and column 0:
///   The minor of row 0 and column 0 is \f$det(\begin{matrix}m_{1,1}\end{matrix}) = m_{1,1}\f$.
///   Hence the cofactor is \f$(-1)^{0+0+2} m_{1,1} = m_{1,1}\f$.
/// * cofactor of row 0 and column 1:
///   The minor of row 0 and column 1 is \f$det(\begin{matrix}m_{1,0}\end{matrix}) = m_{1,0}\f$
///   Hence the cofactor is \f$(-1)^{0+1+2} m_{1,0} = -m_{1,0}\f$.
/// * cofactor of row 1 and column 0:
///   The minor of row 1 and column 0 is \f$det(\begin{matrix}m_{0,1}\end{matrix}) = m_{0,1}\f$.
//    Hence the cofactor is \f$(-1)^{1 + 0 + 2} m_{0,1} = -m_{0,1}\f$.
/// * cofactor of row 1 and column 1:
///   The minor of row 1 and column 1 is \f$det(\begin{matrix}m_{0,0}\end{matrix}) = m_{0,0}\f$.
///   Hence the cofactor is \f$(-1)^{1+1+2} m_{0,0} = m_{0,0}\f$.
static void
cofactor_2x2
  (
  )
{

  Mkx_Scribe_Cas_EmissionContext* emissionContext = Mkx_Scribe_Cas_EmissionContext_create();
  Mkx_Scribe_Cas_EvaluationVisitor* evaluationVisitor = Mkx_Scribe_Cas_EvaluationVisitor_create();

  Mkx_Scribe_Cas_Node* matrixNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_createMatrix2d(2, 2, Ring2_String_fromC(false, "v")));

  static const char* results[] =
  {
    "v[1,1]",
    "-v[1,0]",
    "-v[0,1]",
    "v[0,0]",
  };

  int64_t k = 0;
  for (int64_t i = 0, n = 2; i < n; ++i)
  {
    for (int64_t j = 0, m = 2; j < m; ++j)
    {
      Mkx_Scribe_Cas_EmissionContext_reset(emissionContext);
      Mkx_Scribe_Cas_Node* cofactorNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_CofactorNode_create(i, j, matrixNode));
      Mkx_Scribe_Cas_Node* evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, cofactorNode);
      Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, evaluatedNode);
      Ring2_String* string = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, emissionContext->outputStringBuffer));
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%s\n"), string);
      if (!Ring2_String_isEqualTo(Ring2_Context_get(), string, Ring2_String_fromC(false, results[k++])))
      {
        Ring1_Status_set(Ring1_Status_TestFailed);
        Ring2_jump();
      }
    }
  }
}

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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&zeroInGroup));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&oneInGroup));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&variableInGroup));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&zeroMatrix));
  /*
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&matrixDeterminant_4x4));
  */
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&variable));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&index1dVariable));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&index2dVariable));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&cofactor_1x1));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&cofactor_2x2));
  Ring2_Context_shutdown();
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerCasTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.CasTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
