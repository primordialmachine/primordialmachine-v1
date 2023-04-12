/// @file Ring3/Gdl/Test/UnparseTest1.c
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring3/Gdl/Test/UnparseTest1.h"
#include "Ring3/Gdl/_Include.h"

#include "Ring1/All/_Include.h"

#define DEFINE(NAME, CREATEINPUT, EXPECTED) \
  static void \
  test_##NAME \
    ( \
      Ring2_Context* ctx, \
      Ring2_Value *result, \
      size_t numberOfArguments, \
      Ring2_Value const *arguments \
    ) \
  { \
    Machine_Gdl_Node* node = CREATEINPUT(); \
    Ring2_String* outputName = Ring2_String_fromC(false, #NAME); \
    Ring2_String* expected = Ring2_String_fromC(false, EXPECTED); \
    on(ctx, node, outputName, expected); \
  }

static void
on
  (
    Ring2_Context* ctx,
    Machine_Gdl_Node *node,
    Ring2_String *outputName,
    Ring2_String *expected
  )
{
  Ring2_StringBuffer* outputStringBuffer = Ring2_StringBuffer_create();
  Machine_Gdl_Unparser *unparser = Machine_Gdl_Unparser_create();
  Machine_Gdl_Unparser_unparse(unparser, node, outputName, outputStringBuffer);
  Ring2_String *received = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object *, outputStringBuffer));
  {
    RING2_TEST_ASSERT(Ring2_String_isEqualTo(Ring2_Context_get(), received, expected));
  }
}

static Machine_Gdl_Node *
createEmptyList
  (
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerVoid();
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_List, &v);
}

DEFINE(emptyList, createEmptyList, "[\n]\n")

static Machine_Gdl_Node *
createEmptyMap
  (
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerVoid();
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Map, &v);
}

DEFINE(emptyMap, createEmptyMap, "{\n}\n")

static Machine_Gdl_Node *
createBooleanFalse
  (
  )
{
  Machine_Object* o = Ring1_cast(Machine_Object*,
                                 Ring3_Gdl_BooleanLiteral_create(Ring2_String_fromC(false, "false")));
  Ring2_Value v = Ring2_Value_StaticInitializerObject(o);
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Boolean, &v);
}

DEFINE(booleanFalse, createBooleanFalse, "false")

static Machine_Gdl_Node *
createString
  (
  )
{
  Machine_Object* o = Ring1_cast(Machine_Object*,
                                 Ring3_Gdl_StringLiteral_create(Ring2_String_fromC(false, "\"Hello, World!\"")));
  Ring2_Value v = Ring2_Value_StaticInitializerObject(o);
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_String, &v);
}

DEFINE(string, createString, "\"Hello, World!\"")

static Machine_Gdl_Node *
createBooleanTrue
  (
  )
{
  Machine_Object* o = Ring1_cast(Machine_Object*,
                                 Ring3_Gdl_BooleanLiteral_create(Ring2_String_fromC(false, "true")));
  Ring2_Value v = Ring2_Value_StaticInitializerObject(o);
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Boolean, &v);
}

DEFINE(booleanTrue, createBooleanTrue, "true")

static Machine_Gdl_Node *
createInteger
  (
  )
{
  Machine_Object* o = Ring1_cast(Machine_Object*,Ring3_Gdl_IntegerLiteral_create(Ring2_String_fromC(false, "-1")));
  Ring2_Value v = Ring2_Value_StaticInitializerObject(o);
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Integer, &v);
}

DEFINE(integer, createInteger, "-1")

static Machine_Gdl_Node *
createReal
  (
  )
{
  Machine_Object* o = Ring1_cast(Machine_Object*, Ring3_Gdl_RealLiteral_create(Ring2_String_fromC(false, "-1.0")));
  Ring2_Value v = Ring2_Value_StaticInitializerObject(o);
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Real, &v);
}

DEFINE(real, createReal, "-1.0")

static Machine_Gdl_Node *
createVoid
  (
  )
{
  Machine_Object* o = Ring1_cast(Machine_Object*, Ring3_Gdl_VoidLiteral_create(Ring2_String_fromC(false, "void")));
  Ring2_Value v = Ring2_Value_StaticInitializerObject(o);
  return Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Void, &v);
}

DEFINE(void, createVoid, "void")

void
Ring3_Gdl_Test_registerUnparseTest1
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_fromC(false, "Ring3.Gdl.Test.UnparseTest1");
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".booleanFalse")),
                      &test_booleanFalse);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".booleanTrue")),
                      &test_booleanTrue);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".emptyList")),
                      &test_emptyList);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".emptyMap")),
                      &test_emptyMap);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".integer")),
                      &test_integer);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".real")),
                      &test_real);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".string")),
                      &test_string);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".void")),
                      &test_void);
}
