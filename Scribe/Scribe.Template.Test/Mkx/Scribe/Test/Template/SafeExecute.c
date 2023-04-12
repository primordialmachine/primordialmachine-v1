#include "Mkx/Scribe/Test/Template/SafeExecute.h"

#include "Mkx/Scribe/Environment/Environment.h"
#include "Mkx/Scribe/Template/EvaluateNode.h"
#include "Mkx/Scribe/Template/Library.h"
#include "Mkx/Scribe/Template/parseEnvironment.h"
#include "Mkx/Scribe/Test/Template/SafeExecute.h"

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Template_Test_safeExecute
  (
    bool expectSuccess,
    void (*function)()
  )
{
  bool success = Ring1_Result_Success == Mkx_Scribe_Test_safeExecute(function);
  return success == expectSuccess ? Ring1_Result_Success : Ring1_Result_Failure;
}

void
Mkx_Scribe_Template_Test_execute
  (
    Ring2_Context* ctx,
    const char* configurationPathName,
    const char* sourcePathName,
    const char* targetPathName
  )
{
  // Create the root environment.
  Mkx_Scribe_Environment* rootEnvironment = Mkx_Scribe_Environment_create();
  // Merge library into root environment.
  Mkx_Scribe_Template_Library_register(rootEnvironment);
  // Load the configuration.
  Ring2_String* configurationPathName_ = Ring2_String_fromC(false, configurationPathName);
  Ring2_String* configurationString = Machine_getFileContentsAsString(configurationPathName_);
  Mkx_Scribe_Environment* configEnvironment =
    Mkx_Template_parseEnvironment
      (
        Mkx_SymbolScanner_create(configurationString, configurationPathName_)
      );
  // Merge configuration environment into root environment.
  Mkx_Scribe_Environment_setAll(rootEnvironment, configEnvironment);
  //  Input and output.
  Ring2_String* sourcePathName_ = Ring2_String_fromC(false, sourcePathName);
  Ring2_String* targetPathName_ = Ring2_String_fromC(false, targetPathName);

  Mkx_Scribe_Hll_Node* taskNode = Mkx_Scribe_Hll_Node_createTask(NULL);
  Mkx_Scribe_Hll_Node* sourcePathNameNode =
    Mkx_Scribe_Hll_Node_createStringLiteral(NULL, sourcePathName_);
  Mkx_Scribe_Hll_Node* targetPathNameNode =
    Mkx_Scribe_Hll_Node_createStringLiteral(NULL, targetPathName_);
  Mkx_Scribe_Hll_Node_append(taskNode, sourcePathNameNode);
  Mkx_Scribe_Hll_Node_append(taskNode, targetPathNameNode);

  Mkx_Template_evaluateNode(taskNode, rootEnvironment);
}
