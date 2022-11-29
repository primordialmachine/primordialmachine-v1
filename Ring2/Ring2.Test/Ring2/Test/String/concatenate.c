// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/String/concatenate.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/String/concatenate.h"

static void
test
  (
    Ring2_String* a,
    Ring2_String* b
  )
{
  Ring2_String* c = Ring2_String_concatenate(Ring2_Context_get(), a, b);
  int64_t i = Ring2_String_getNumberOfBytes(a),
          j = Ring2_String_getNumberOfBytes(b),
          k = Ring2_String_getNumberOfBytes(c);
  MKX_TEST_ASSERT_EQ(context, i + j, k);
  MKX_TEST_ASSERT_EQ(context, true,Ring2_String_isEqualTo(Ring2_Context_get(), Ring2_String_substring(Ring2_Context_get(), c, 0, i), a));
  MKX_TEST_ASSERT_EQ(context, true,Ring2_String_isEqualTo(Ring2_Context_get(), Ring2_String_substring(Ring2_Context_get(), c, i, j), b));
}

void
Mkx_Interpreter_Test_String_concatenate
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
  } Fixture;
  static const Fixture g_fixtures[] =
  {
    { { "",  0 }, {  "", 0 } },
    { { "",  0 }, { "x", 1 } },
    { { "x", 1 }, {  "", 0 } },
    { { "x", 1 }, { "x", 1 } },
  };
  for (int64_t i = 0, n = 4; i < n; ++i)
  {
    Ring2_String* a = Ring2_String_create(g_fixtures[i].lhs.bytes, g_fixtures[i].lhs.numberOfBytes);
    Ring2_String* b = Ring2_String_create(g_fixtures[i].rhs.bytes, g_fixtures[i].rhs.numberOfBytes);
    test(a, b);
  }
}
