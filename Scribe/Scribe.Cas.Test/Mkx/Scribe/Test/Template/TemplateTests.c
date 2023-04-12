#include "Mkx/Scribe/Test/Template/TemplateTests.h"

#include "Mkx/Scribe/Environment/Environment.h"
#include "Mkx/Scribe/Template/EvaluateNode.h"
#include "Mkx/Scribe/Template/Library.h"
#include "Mkx/Scribe/Template/parseEnvironment.h"
#include "Mkx/Scribe/Test/Template/SafeExecute.h"

static void
execute
  (
    Mkx_Interpreter_Context* ctx,
    const char* configurationPathName,
    const char* sourcePathName,
    const char* targetPathName
  )
{
  // Create the root environment.
  Mkx_Scribe_Environment* rootEnvironment =
    Mkx_Scribe_Environment_create(ctx);
  // Merge library into root environment.
  Mkx_Scribe_Template_Library_register(ctx, rootEnvironment);
  // Load the configuration.
  Mkx_Interpreter_String* configurationPathName_ =
    Mkx_Interpreter_Ffi_String_create(ctx, configurationPathName);
  Mkx_Interpreter_String* configurationString =
    Mkx_Interpreter_Library_getFileContents(ctx, configurationPathName_);
  Mkx_Scribe_Environment* configEnvironment = Mkx_Template_parseEnvironment(
    ctx, Mkx_SymbolScanner_create(ctx, configurationString, configurationPathName_));
  // Merge configuration environment into root environment.
  Mkx_Scribe_Environment_setAll(ctx, rootEnvironment, configEnvironment);
  //  Input and output.
  Mkx_Interpreter_String* sourcePathName_ = Mkx_Interpreter_Ffi_String_create(
    ctx, sourcePathName);
  Mkx_Interpreter_String* targetPathName_ = Mkx_Interpreter_Ffi_String_create(
    ctx, targetPathName);

  Mkx_Scribe_Hll_Node* taskNode = Mkx_Scribe_Hll_Node_createTask(ctx, NULL);
  Mkx_Scribe_Hll_Node* sourcePathNameNode =
    Mkx_Scribe_Hll_Node_createStringLiteral(ctx, NULL, sourcePathName_);
  Mkx_Scribe_Hll_Node* targetPathNameNode =
    Mkx_Scribe_Hll_Node_createStringLiteral(ctx, NULL, targetPathName_);
  Mkx_Scribe_Hll_Node_append(ctx, taskNode, sourcePathNameNode);
  Mkx_Scribe_Hll_Node_append(ctx, taskNode, targetPathNameNode);

  Mkx_Template_evaluateNode(ctx, taskNode, rootEnvironment);
}

// multi-line comments
static void
multiLineComments
  (
    Mkx_Interpreter_Context *ctx
  )
{
  execute(ctx,
          "multiLineComment1/1.configuration",
          "multiLineComment1/1.html.template",
          "multiLineComment1/1.html");
}

static void
stringVariableEvaluation
  (
    Mkx_Interpreter_Context* ctx
  )
{
  execute(ctx,
          "stringVariableEvaluation/1.configuration",
          "stringVariableEvaluation/1.html.template",
          "stringVariableEvaluation/1.html");
}

static void
stringLiteralEvaluation
  (
    Mkx_Interpreter_Context* ctx
  )
{
  execute(ctx,
          "stringLiteralEvaluation/1.configuration",
          "stringLiteralEvaluation/1.html.template",
          "stringLiteralEvaluation/1.html");
}

#define Test(TEST_NAME,FUNCTION_NAME) \
  static void \
  TEST_NAME(Ring1_Test_Context* ctx) { \
    Mkx_Interpreter_Context* context = Mkx_Interpreter_Context_create(); \
    RING1_TEST_ASSERT_NOTNULL(ctx, context); \
    if (!context) { \
      return; \
    } \
    RING1_TEST_ASSERT_EQ(ctx, 0, \
                        Mkx_Scribe_Template_Test_safeExecute(context, \
                                                             &FUNCTION_NAME)); \
    Mkx_Interpreter_Context_destroy(context); \
  }

Test(multiLineCommentsTest, multiLineComments)
Test(stringVariableEvaluationTest, stringVariableEvaluation)
Test(stringLiteralEvaluationTest, stringLiteralEvaluation)

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
      Ring1_Test_Context_addTest(ctx, "Mkx.Scribe.Test.stringLiteralEvaluation", &stringLiteralEvaluationTest))) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
