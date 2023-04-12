#include "Mkx/Scribe/Test/Cas/CasConstantFoldingTests.h"


#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


// Assert "0" yields "0".
TestBegin(zero, "0", "0")
{
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1" yields "1".
TestBegin(one, "1", "1")
{
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 + 0" yields "1".
TestBegin(onePlusZero, "1 + 0", "1")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  Mkx_Scribe_Cas_Node* rightOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(context, leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "0 + 1" yields "1".
TestBegin(zeroPlusOne, "0 + 1", "1")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
  Mkx_Scribe_Cas_Node* rightOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(context, leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "0 * 1" yields "0".
TestBegin(zeroStarOne, "0 * 1", "0")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
  Mkx_Scribe_Cas_Node* rightOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(context, leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 * 0" yields "0".
TestBegin(oneStarZero, "1 * 0", "0")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  Mkx_Scribe_Cas_Node* rightOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(context, leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 - 1" yields "0".
TestBegin(oneMinusOne, "1 - 1", "0")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  Mkx_Scribe_Cas_Node* rightOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(context, leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 - 0" yields "0".
TestBegin(oneMinusZero, "1 - 0", "1")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  Mkx_Scribe_Cas_Node* rightOperandNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(context, leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "+1" yields "1".
TestBegin(plusOne, "+1", "1")
{
  Mkx_Scribe_Cas_Node* operand = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create(context));
  
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_UnaryPlusNode_create(context, operand));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(context, evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "+0" yields "0".
TestBegin(plusZero, "+0", "0")
{
  Mkx_Scribe_Cas_Node* operand = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create(context));
 
  unevaluatedNode = Mkx_Intrinsic_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_UnaryPlusNode_create(context, operand));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &one));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &zero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &onePlusZero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &zeroPlusOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &oneStarZero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &zeroStarOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &oneMinusOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &oneMinusZero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &plusOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(context, &plusZero));
  Mkx_Interpreter_Context_destroy(context);
}

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerConstantFoldingTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Cas.Test.ConstantFoldingTests", &test))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
