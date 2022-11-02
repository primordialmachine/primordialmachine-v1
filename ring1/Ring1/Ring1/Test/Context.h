#if !defined(RING1_TEST_CONTEXT_H_INCLUDED)
#define RING1_TEST_CONTEXT_H_INCLUDED

#if !defined(RING1_TEST_PRIVATE) || 1 != RING1_TEST_PRIVATE
#error("Do not include `Ring1/Test/Context.h` directly. Include `Ring1/Test.h` instead.")
#endif

#include "Ring1/Test.h"

struct Ring1_Test_Context
{
  /// @brief The list of root nodes.
  Ring1_Test_Node* nodes;
  /// @brief The node currently being evaluated.
  Ring1_Test_Node* currentNode;
};

#endif // RING1_TEST_CONTEXT_H_INCLUDED
