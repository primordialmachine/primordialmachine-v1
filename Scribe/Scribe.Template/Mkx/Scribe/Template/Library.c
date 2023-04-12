#include "Mkx/Scribe/Template/Library.h"

static void
getGeneratorName
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushString(context, Ring2_String_fromC(false, "Scribe"));
}

static void
getGeneratorVendor
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushString(context, Ring2_String_fromC(false, "Primordial Machine"));
}

void
Mkx_Scribe_Template_Library_register
  (
    Mkx_Scribe_Environment* environment
  )
{
  Mkx_Scribe_Variable* variable;

  variable = Mkx_Scribe_Variable_create(Ring2_String_fromC(false, "GeneratorVendor"));
  Mkx_Scribe_Variable_setForeignFunctionValue(variable, &getGeneratorVendor);
  Mkx_Scribe_Environment_set(environment, variable);

  variable = Mkx_Scribe_Variable_create(Ring2_String_fromC(false, "GeneratorName"));
  Mkx_Scribe_Variable_setForeignFunctionValue(variable, &getGeneratorName);
  Mkx_Scribe_Environment_set(environment, variable);
}
