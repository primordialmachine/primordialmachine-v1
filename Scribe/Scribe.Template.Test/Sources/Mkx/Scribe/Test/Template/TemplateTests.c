#include "Mkx/Scribe/Test/Template/TemplateTests.h"

#include "Mkx/Scribe/Environment/Environment.h"
#include "Mkx/Scribe/Template/EvaluateNode.h"
#include "Mkx/Scribe/Template/Library.h"
#include "Mkx/Scribe/Template/parseEnvironment.h"
#include "Mkx/Scribe/Test/Template/SafeExecute.h"

// multi-line comments
static void
multiLineComments
  (
  )
{
  Mkx_Scribe_Template_Test_execute(Ring2_Context_get(),
                                   "multiLineComment1/1.configuration",
                                   "multiLineComment1/1.html.template",
                                   "multiLineComment1/1.html");
}

static void
stringVariableEvaluation
  (
  )
{
  Mkx_Scribe_Template_Test_execute(Ring2_Context_get(),
                                   "stringVariableEvaluation/1.configuration",
                                   "stringVariableEvaluation/1.html.template",
                                   "stringVariableEvaluation/1.html");
}

static void
stringLiteralEvaluation
  (
  )
{
  Mkx_Scribe_Template_Test_execute(Ring2_Context_get(),
                                   "stringLiteralEvaluation/1.configuration",
                                   "stringLiteralEvaluation/1.html.template",
                                   "stringLiteralEvaluation/1.html");
}

static void
stringLiteralConcatenation
  (
  )
{
  Mkx_Scribe_Template_Test_execute(Ring2_Context_get(),
                                   "stringLiteralConcatenation/1.configuration",
                                   "stringLiteralConcatenation/1.html.template",
                                   "stringLiteralConcatenation/1.html");
}

#define Test(TEST_NAME,FUNCTION_NAME) \
  static Ring1_Result \
  TEST_NAME(Ring1_Test_Context* ctx) { \
    Ring1_Result result; \
    if (result = Ring2_Context_startup()) { \
      RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success); \
      return Ring1_Result_Failure; \
    } \
    RING1_TEST_ASSERT_EQ(ctx, 0, \
                        Mkx_Scribe_Template_Test_safeExecute(true, \
                                                             &FUNCTION_NAME)); \
    Ring2_Context_shutdown(); \
    return Ring1_Result_Success; \
  }

Test(multiLineCommentsTest, multiLineComments)
Test(stringVariableEvaluationTest, stringVariableEvaluation)
Test(stringLiteralEvaluationTest, stringLiteralEvaluation)
Test(stringLiteralConcatenationTest, stringLiteralConcatenation)

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Template_Test_registerTemplateTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Unlikely(!ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(
      Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Test.multiLineCommentTest", &multiLineCommentsTest) ||
      Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Test.stringVariableEvaluation", &stringVariableEvaluationTest) ||
      Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Test.stringLiteralEvaluation", &stringLiteralEvaluationTest) ||
      Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Test.stringLiteralConcatenation", &stringLiteralConcatenationTest))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
