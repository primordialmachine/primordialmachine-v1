#if !defined(RING1_TEST_CONTEXT_H_INCLUDED)
#define RING1_TEST_CONTEXT_H_INCLUDED

#include "Ring1/Test/Commons.h"

struct Ring1_Test_Context
{
  /// @brief The list of root nodes.
  Ring1_Test_Node* nodes;
  /// @brief The node currently being evaluated.
  Ring1_Test_Node* currentNode;
};

#endif // RING1_TEST_CONTEXT_H_INCLUDED
