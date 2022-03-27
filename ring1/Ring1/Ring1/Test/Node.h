// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Test/Node.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_TEST_NODE_H_INCLUDED)
#define RING1_TEST_NODE_H_INCLUDED

#if !defined(RING1_TEST_INTERNAL) || 1 != RING1_TEST_INTERNAL
#error("Do not include `Ring1/Test/Node.h` directly. Include `Ring1/Test.h` instead.")
#endif

#include "Ring1/Test/Commons.h"

/// @todo Should not be part of the public API.
/// @brief Indicates a test node was not evaluated.
/// Mutually exclusive with RING1_TEST_NODE_FLAG_ISEVALUTING and RING1_TEST_NODE_FLAG_ISEVALUATED.
#define RING1_TEST_NODE_FLAG_ISNOTEVALUATED (1)

/// @todo Should not be part of the public API.
/// @brief Indicates a test node is evaluating.
/// Mutually exclusive with RING1_TEST_NODE_FLAG_ISNOTEVALUATED and RING1_TEST_NODE_FLAG_ISEVALUATED.
#define RING1_TEST_NODE_FLAG_ISEVALUATING (2)

/// @todo Should not be part of the public API.
/// @brief Indicates a test node was evaluated.
/// Mutually exclusive with RING1_TEST_NODE_FLAG_ISNOTEVALUATED and RING1_TEST_NODE_FLAG_ISEVALUATING.
#define RING1_TEST_NODE_FLAG_ISEVALUATED (4)

/// @todo Should not be part of the public API.
/// @brief Indicates a test node has errors.
/// Mutually exclusive with RING1_TEST_NODE_FLAG_NOTEVALUATED.
#define RING1_TEST_NODE_FLAG_HASERRORS (8)

/// @todo Should not be part of the public API.
struct Ring1_Test_Node
{
  Ring1_Test_Node* next;
  char* name;
  int flags;
  Ring1_Test_Function* function;
};

/// @todo Should not be part of the public API.
Ring1_CheckReturn() Ring1_Result
Ring1_Test_Node_create
  (
    Ring1_Test_Node** node,
    const char* name,
    Ring1_Test_Function* function
  );

/// @todo Should not be part of the public API.
void
Ring1_Test_Node_destroy
  (
    Ring1_Test_Node* node
  );


#endif // RING1_TEST_NODE_H_INCLUDED
