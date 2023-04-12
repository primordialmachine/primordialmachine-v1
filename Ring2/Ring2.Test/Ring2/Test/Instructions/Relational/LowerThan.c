#include "Ring2/Test/Instructions/Relational/EqualTo.h"

static void
testLowerThanBoolean
  (
    Ring2_Context* context
  )
{
  typedef struct Specificiation
  {
    Ring2_Boolean x;
    Ring2_Boolean y;
    Ring2_Boolean z;
  } Specification;
  static const Specification specifications[] =
  {
    {.x = Ring2_Boolean_False,.y = Ring2_Boolean_False,.z = Ring2_Boolean_False  },
    {.x = Ring2_Boolean_False,.y = Ring2_Boolean_True,.z = Ring2_Boolean_True },
    {.x = Ring2_Boolean_True,.y = Ring2_Boolean_False,.z = Ring2_Boolean_False },
    {.x = Ring2_Boolean_True,.y = Ring2_Boolean_True,.z = Ring2_Boolean_False  },
  };
  size_t numberOfSpecificiations = sizeof(specifications) / sizeof(Specification);
  //
  for (size_t i = 0, n = numberOfSpecificiations; i < n; ++i)
  {
    Mkx_Interpreter_Stack_pushBoolean(context, specifications[i].x);
    Mkx_Interpreter_Stack_pushBoolean(context, specifications[i].y);
    Mkx_Interpreter_Instructions_lowerThan(context);
    Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
    MKX_TEST_ASSERT_NEQ(context, value, NULL);
    MKX_TEST_ASSERT_EQ(context, Ring2_Value_isBoolean(value), true);
    MKX_TEST_ASSERT_EQ(context, Ring2_Value_getBoolean(value), specifications[i].z);
    Mkx_Interpreter_Stack_pop(context, 1);
  }
}

static void
testLowerThanInteger
  (
    Ring2_Context* context
  )
{
  typedef struct Specificiation
  {
    Ring2_Integer x;
    Ring2_Integer y;
    Ring2_Boolean z;
  } Specification;
  static const Specification specifications[] =
  {
    {.x = 0,.y = 0,.z = Ring2_Boolean_False  },
    {.x = 0,.y = 1,.z = Ring2_Boolean_True },
    {.x = 1,.y = 0,.z = Ring2_Boolean_False },
    {.x = 1,.y = 1,.z = Ring2_Boolean_False  },
  };
  size_t numberOfSpecificiations = sizeof(specifications) / sizeof(Specification);
  //
  for (size_t i = 0, n = numberOfSpecificiations; i < n; ++i)
  {
    Mkx_Interpreter_Stack_pushInteger(context, specifications[i].x);
    Mkx_Interpreter_Stack_pushInteger(context, specifications[i].y);
    Mkx_Interpreter_Instructions_lowerThan(context);
    Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
    MKX_TEST_ASSERT_NEQ(context, value, NULL);
    MKX_TEST_ASSERT_EQ(context, Ring2_Value_isBoolean(value), true);
    MKX_TEST_ASSERT_EQ(context, Ring2_Value_getBoolean(value), specifications[i].z);
    Mkx_Interpreter_Stack_pop(context, 1);
  }
}

static void
testLowerThanReal
  (
    Ring2_Context* context
  )
{
  typedef struct Specificiation
  {
    Ring2_Real64 x;
    Ring2_Real64 y;
    Ring2_Boolean z;
  } Specification;
  static const Specification specifications[] =
  {
    {.x = 0.,.y = 0.,.z = Ring2_Boolean_False },
    {.x = 0.,.y = 1.,.z = Ring2_Boolean_True },
    {.x = 1.,.y = 0.,.z = Ring2_Boolean_False },
    {.x = 1.,.y = 1.,.z = Ring2_Boolean_False },
  };
  size_t numberOfSpecificiations = sizeof(specifications) / sizeof(Specification);
  //
  for (size_t i = 0, n = numberOfSpecificiations; i < n; ++i)
  {
    Mkx_Interpreter_Stack_pushReal(context, specifications[i].x);
    Mkx_Interpreter_Stack_pushReal(context, specifications[i].y);
    Mkx_Interpreter_Instructions_lowerThan(context);
    Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
    MKX_TEST_ASSERT_NEQ(context, value, NULL);
    MKX_TEST_ASSERT_EQ(context, Ring2_Value_isBoolean(value), true);
    MKX_TEST_ASSERT_EQ(context, Ring2_Value_getBoolean(value), specifications[i].z);
    Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
  }
}

void
Ring2_Test_Instructions_Relational_testLowerThan
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  testLowerThanBoolean(context);
  testLowerThanInteger(context);
  testLowerThanReal(context);
}
