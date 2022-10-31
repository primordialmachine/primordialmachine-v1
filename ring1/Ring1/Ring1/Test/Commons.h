#if !defined(RING1_TEST_COMMONS_H_INCLUDED)
#define RING1_TEST_COMMONS_H_INCLUDED

#if !defined(RING1_TEST_PRIVATE) || 1 != RING1_TEST_PRIVATE
#error("Do not include `Ring1/Test/Commons.h` directly. Include `Ring1/Test.h` instead.")
#endif

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

// @brief Type of a test context.
typedef struct Ring1_Test_Context Ring1_Test_Context;

/// @brief Type of a test node.
typedef struct Ring1_Test_Node Ring1_Test_Node;

/// @brief Type of a test function.
typedef void Ring1_Test_Function(Ring1_Test_Context*);

#endif // RING1_TEST_COMMONS_H_INCLUDED
