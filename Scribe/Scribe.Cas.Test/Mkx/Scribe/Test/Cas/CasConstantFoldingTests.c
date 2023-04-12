#include "Mkx/Scribe/Test/Cas/CasConstantFoldingTests.h"


#include "Ring2/_Include.h"
#include "Mkx/Scribe/Test/Cas/SafeExecute.h"


// Assert "0" yields "0".
TestBegin(zero, "0", "0")
{
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1" yields "1".
TestBegin(one, "1", "1")
{
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 + 0" yields "1".
TestBegin(onePlusZero, "1 + 0", "1")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  Mkx_Scribe_Cas_Node* rightOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "0 + 1" yields "1".
TestBegin(zeroPlusOne, "0 + 1", "1")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  Mkx_Scribe_Cas_Node* rightOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "0 * 1" yields "0".
TestBegin(zeroStarOne, "0 * 1", "0")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  Mkx_Scribe_Cas_Node* rightOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 * 0" yields "0".
TestBegin(oneStarZero, "1 * 0", "0")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  Mkx_Scribe_Cas_Node* rightOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 - 1" yields "0".
TestBegin(oneMinusOne, "1 - 1", "0")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  Mkx_Scribe_Cas_Node* rightOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "1 - 0" yields "0".
TestBegin(oneMinusZero, "1 - 0", "1")
{
  Mkx_Scribe_Cas_Node* leftOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  Mkx_Scribe_Cas_Node* rightOperandNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(leftOperandNode, rightOperandNode));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "+1" yields "1".
TestBegin(plusOne, "+1", "1")
{
  Mkx_Scribe_Cas_Node* operand = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_UnaryPlusNode_create(operand));
  evaluatedNode = Mkx_Scribe_Cas_EvaluationVisitor_evaluate(evaluationVisitor, unevaluatedNode);
}
TestEnd()

// Assert "+0" yields "0".
TestBegin(plusZero, "+0", "0")
{
  Mkx_Scribe_Cas_Node* operand = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
 
  unevaluatedNode = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_UnaryPlusNode_create(operand));
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
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&one));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&zero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&onePlusZero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&zeroPlusOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&oneStarZero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&zeroStarOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&oneMinusOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&oneMinusZero));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&plusOne));
  RING1_TEST_ASSERT_EQ(ctx, 0, Mkx_Scribe_Cas_Test_safeExecute(&plusZero));
  Ring2_Context_shutdown();
  return Ring1_Result_Success;
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
