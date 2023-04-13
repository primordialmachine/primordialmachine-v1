// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/String/firstOccurrenceOf.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/String/firstOccurrenceOf.h"

static void
test
  (
    Ring2_String* a,
    Ring2_String* b,
    int64_t index
  )
{
  int64_t i = Ring2_String_firstOccurrenceOf(Ring2_Context_get(), a, b);
  MKX_TEST_ASSERT_EQ(context, i, index);
}

void
Mkx_Interpreter_Test_String_firstOccurrenceOf
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{

  typedef struct Fixture
  {
    const StringFixture lhs;
    const StringFixture rhs;
    const int64_t index;
  } Fixture;
  static const Fixture g_fixtures[] =
  {
    { { "",  0 }, {  "", 0 },  0 },
    { { "",  0 }, { "x", 1 }, -1 },
    { { "x", 1 }, {  "", 0 },  0 },
    { { "x", 1 }, { "x", 1 },  0 },
    //
    { { "x", 1 }, { "y", 1 }, -1 },
    { { "y", 1 }, { "x", 1 }, -1 },
    //
    { { "xyy",  3 }, { "yy", 2 },  1 },
    { { "xyyy", 4 }, { "yy", 2 },  1 },
  };
  for (int64_t i = 0, n = 8; i < n; ++i)
  {
    Ring2_String* a = Ring2_String_create(g_fixtures[i].lhs.bytes, g_fixtures[i].lhs.numberOfBytes);
    Ring2_String* b = Ring2_String_create(g_fixtures[i].rhs.bytes, g_fixtures[i].rhs.numberOfBytes);
    test(a, b, g_fixtures[i].index);
  }
}
