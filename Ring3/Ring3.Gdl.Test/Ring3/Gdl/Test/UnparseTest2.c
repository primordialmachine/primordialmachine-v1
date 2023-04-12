/// @file Ring3/Gdl/Test/UnparseTest2.c
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring3/Gdl/Test/UnparseTest2.h"
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
    Machine_setFileContentsString(Ring2_String_fromC(false, ".received"), received);
    Machine_setFileContentsString(Ring2_String_fromC(false, ".expected"), expected);
    RING2_TEST_ASSERT(Ring2_String_isEqualTo(Ring2_Context_get(), received, expected));
  }
}

/// <code>
/// {
///   x : {
///   }
/// }
/// </code> 
static Machine_Gdl_Node *
createFormattedMap1
  (
  )
{ 
  static const Ring2_Value voidValue = Ring2_Value_StaticInitializerVoid();
  Machine_Gdl_Node *root = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Map, &voidValue); 
  //
  Machine_Gdl_Node *pair = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Pair, &voidValue);  
  {
    Ring2_Value v = Ring2_Value_StaticInitializerObject(Ring1_cast(Machine_Object*, Ring3_Gdl_Name_create(Ring2_String_fromC(false, "x"))));
    Machine_Gdl_Node* key = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Name, &v);
    Machine_Gdl_Node* value = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Map, &voidValue);
    Machine_Gdl_Node_append(pair, key);
    Machine_Gdl_Node_append(pair, value);
  }
  Machine_Gdl_Node_append(root, pair);
  return root;
}

DEFINE
  (
    map, createFormattedMap1,
    "{\n"
    "  x : {\n"
    "  }\n"
    "}\n"
  )

/// <code>
/// {
///   x : [
///   ]
/// }
/// </code> 
static Machine_Gdl_Node *
createFormattedList1
  (
  )
{ 
  static const Ring2_Value voidValue = Ring2_Value_StaticInitializerVoid();
  Machine_Gdl_Node *root = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Map, &voidValue); 
  //
  Machine_Gdl_Node *pair = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Pair, &voidValue);
  {
    Ring2_Value v = Ring2_Value_StaticInitializerObject(Ring1_cast(Machine_Object*,Ring3_Gdl_Name_create(Ring2_String_fromC(false, "x"))));
    Machine_Gdl_Node* key = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_Name, &v);
    Machine_Gdl_Node* value = Machine_Gdl_Node_create(Machine_Gdl_NodeKind_List, &voidValue);
    Machine_Gdl_Node_append(pair, key);
    Machine_Gdl_Node_append(pair, value);
  }
  Machine_Gdl_Node_append(root, pair);
  return root;
}

DEFINE
  (
    list,
    createFormattedList1,
    "{\n"
    "  x : [\n"
    "  ]\n"
    "}\n"
  )

void
Ring3_Gdl_Test_registerUnparseTest2
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_fromC(false, "Ring3.Gdl.Test.UnparseTest2");
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".mapFormatting1")),
                      &test_map);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                               Ring2_String_fromC(false, ".listFormatting1")),
                      &test_list);
}
