// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Test.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TEST_H_INCLUDED)
#define RING2_TEST_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Test/Tests.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/TypeSystem/ClassType.h"
#include "Ring2/Types/Value.h"

/// @todo Should not be part of the public API.
/// @brief Indicates a test node was not evaluated.
/// Mutually exclusive with RING2_TEST_FLAG_ISEVALUTING and RING2_TEST_FLAG_ISEVALUATED.
#define RING2_TEST_FLAG_ISNOTEVALUATED (1)

/// @todo Should not be part of the public API.
/// @brief Indicates a test node is evaluating.
/// Mutually exclusive with RING2_TEST_FLAG_ISNOTEVALUATED and RING2_TEST_FLAG_ISEVALUATED.
#define RING2_TEST_FLAG_ISEVALUATING (2)

/// @todo Should not be part of the public API.
/// @brief Indicates a test node was evaluated.
/// Mutually exclusive with RING2_TEST_FLAG_ISNOTEVALUATED and RING2_TEST_FLAG_ISEVALUATING.
#define RING2_TEST_FLAG_ISEVALUATED (4)

/// @todo Should not be part of the public API.
/// @brief Indicates a test node has errors.
/// Mutually exclusive with RING2_TEST_FLAG_NOTEVALUATED.
#define RING2_TEST_FLAG_HASERRORS (8)

MACHINE_DECLARE_CLASSTYPE(Ring2_Test)

struct Ring2_Test_Class {
  Machine_Object_Class _parent;
};

struct Ring2_Test {
  Machine_Object _parent;
  Ring2_String* name;
  Ring2_ForeignProcedure* procedure;
  Ring2_Integer flags;
};

/// <code>
/// (String, Procedure)
/// </code> 
void
Ring2_Test_construct
  (
    Ring2_Test *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );
  
Ring2_Test *
Ring2_Test_create
  (
    Ring2_String *name,
    Ring2_ForeignProcedure *procedure
  );

#define RING2_TEST_ASSERT(e) \
  if (!(e)) { \
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "test assertion `%s` failed\n", #e); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  }

#endif // RING2_TEST_INCLUDED
