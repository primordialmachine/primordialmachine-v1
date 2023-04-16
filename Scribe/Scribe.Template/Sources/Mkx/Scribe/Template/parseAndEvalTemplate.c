#include "Mkx/Scribe/Template/parseAndEvalTemplate.h"


#include "Mkx/Scribe/Template/parseTemplate.h"
#include "Mkx/Scribe/Template/EvaluateNode.h"
#include "Mkx/Scribe/Hll.h"
#include "Mkx/Scribe/Common.h"


void
Mkx_Template_parseAndEvalTemplate
  (
    Ring2_String* pathname,
    Mkx_Scribe_Environment* env,
    Ring2_StringBuffer* output
  )
{
  // Get the file contents.
  Ring2_String* source = Machine_getFileContentsAsString(pathname);
  // Initialize a scanner.
  Mkx_SymbolScanner* symbolScanner = Mkx_SymbolScanner_create(source, pathname);
  // Parse the template.
  Mkx_Scribe_Hll_Node* templateNode = Mkx_Template_parseTemplate(symbolScanner);
  // Evalute the template.
  int64_t oldStackSize = Mkx_Interpreter_Stack_getSize(Ring2_Context_get());
  Mkx_Template_evaluateNode(templateNode, env);
  int64_t newStackSize = Mkx_Interpreter_Stack_getSize(Ring2_Context_get());
  if (newStackSize < oldStackSize)
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "stack underflow\n"));
    Ring1_Status_set(Ring1_Status_StackCorruption);
    Ring2_jump();
  }
  else if (newStackSize > oldStackSize)
  {
    if (newStackSize - oldStackSize > 1)
    {
      int64_t delta = newStackSize - oldStackSize;
      Mkx_Interpreter_Stack_pop(Ring2_Context_get(), delta);
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "%i return values received, expected %i\n"), delta, 1);
      Ring1_Status_set(Ring1_Status_InvalidNumberOfOutputs);
      Ring2_jump();
    }
    if (!Mkx_Interpreter_Stack_isStringAt(Ring2_Context_get(), 0))
    {
      Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "return value at stack index %i is not of type string\n"));
      Ring1_Status_set(Ring1_Status_InvalidOutputType);
      Ring2_jump();
    }
    Ring2_String* s = Mkx_Interpreter_Stack_getStringAt(Ring2_Context_get(), 0);
    Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
    // Append to buffer.
    Ring2_StringBuffer_appendString(output, s);
  }
}
