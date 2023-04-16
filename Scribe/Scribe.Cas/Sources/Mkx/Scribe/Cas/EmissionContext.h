// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/EmissionContext.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_CAS_EMISSIONCONTEXT_H_INCLUDED)
#define MKX_SCRIBE_CAS_EMISSIONCONTEXT_H_INCLUDED

#include "Mkx/Scribe/Cas/Emit/Cpp/IndexEmissionOptions.h"
#include "Mkx/Scribe/Cas/Emit/Cpp/MatrixEmissionOptions.h"
typedef struct Mkx_Scribe_Cas_Node Mkx_Scribe_Cas_Node; // Forward declaration.


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_EmissionContext)

struct Mkx_Scribe_Cas_EmissionContext_Class {
  Machine_Object_Class _parent;
  
  void
  (*emit)
    (
      Mkx_Scribe_Cas_EmissionContext* self,
      Mkx_Scribe_Cas_Node* node
    );

  void
  (*reduce)
    (
      Mkx_Scribe_Cas_EmissionContext* self
    );

  void
  (*reset)
    (
      Mkx_Scribe_Cas_EmissionContext* self
    );
};

/// @brief An emission context.
/// @detail
/// The emission context uses an input stack and an output stack to produce a string from nodes.
/// Nodes are pushed on the input stack.
/// Until the input stack is empty, nodes are popped from the input stack.
/// If the popped node is an "output" node, it is pushed on the output stack.
/// Otherwise the evalute method of the popped node is invoked.
/// As long as the output stack is not empty, "output" nodes are popped from the output stack and their strings are appended to the output buffer.
///
/// Below there is an example on how an term is processed.
/// On the left, the input stack is displayed. On the right, the output stack contents are displayed.
/// @code
/// [], []
/// @endcode
/// We push a "multiplication" (a + b) * (c + d) on the input stack.
/// @code
/// [(a + b), "*", (c + d)]           []
/// @endcode
/// We invoke "evaluate" on the element on the stack.
/// @code
/// [(a + b), "*", "(", c + d, ")"]   []
/// @endcode
/// Pop "output" nodes until the input stack is empty or a non-"output" node is encountered.
/// @code
/// [(a + b), "*", "(", c + d]        [")"]
/// [(a + b), "*", "(", c, "+", d]    [")"]
/// [(a + b), "*", "(", c, "+", "d"]  [")"]
/// [(a + b), "*", "(", c, "+"]       [")", "d"]
/// [(a + b), "*", "(", c]            [")", "d", "+"]
/// [(a + b), "*", "(", "c"]          [")", "d", "+"]
/// [(a + b), "*", "("]               [")", "d", "+", "c"]
/// [(a + b), "*"]                    [")", "d", "+", "c", ")"]
/// [(a + b)]                         [")", "d", "+", "c", ")", "*"]
/// ["(", a + b, ")"]                 [")", "d", "+", "c", ")", "*"]
/// ["(", a + b]                      [")", "d", "+", "c", ")", "*", ")"]
/// ["(", a, "+", b]                  [")", "d", "+", "c", ")", "*", ")"]
/// ["(", a, "+", "b"]                [")", "d", "+", "c", ")", "*", ")"]
/// ["(", a, "+"]                     [")", "d", "+", "c", ")", "*", ")", "b"]
/// ["(", a]                          [")", "d", "+", "c", ")", "*", ")", "b", "+"]
/// ["(", "a"]                        [")", "d", "+", "c", ")", "*", ")", "b", "+"]
/// ["("]                             [")", "d", "+", "c", ")", "*", ")", "b", "+", "a"]
/// []                                [")", "d", "+", "c", ")", "*", ")", "b", "+", "a", ")"]
/// @endcode
/// As the input stack is empty now, pop the contents of the output stack and append them to the output string buffer.
struct Mkx_Scribe_Cas_EmissionContext {
  Machine_Object _parent;
  Ring2_Collections_Stack* inputStack;
  bool isReducing; /// To prevent recursion of "reduce".
  Ring2_Collections_Stack* outputStack;
  Ring2_StringBuffer* outputStringBuffer;
  /// @brief The matrix emission option.
  Mkx_Scribe_Cas_MatrixEmissionOption matrixEmissionOption;
  /// @brief The index emission option.
  Mkx_Scribe_Cas_IndexEmissionOption indexEmissionOption;
};

void
Mkx_Scribe_Cas_EmissionContext_construct
  (
    Mkx_Scribe_Cas_EmissionContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an emission context.
/// @return The emission context.
Mkx_Scribe_Cas_EmissionContext*
Mkx_Scribe_Cas_EmissionContext_create
  (
  );

/// @brief Emit a node to this emission context.
/// @param context The context.
/// @param self The emission context.
/// @param node The node.
void
Mkx_Scribe_Cas_EmissionContext_emit
  (
    Mkx_Scribe_Cas_EmissionContext* self,
    Mkx_Scribe_Cas_Node* node
  );

void
Mkx_Scribe_Cas_EmissionContext_reduce
  (
    Mkx_Scribe_Cas_EmissionContext* self
  );

/// @brief Reset this emission context.
/// @detail The output stack and the input stack are cleared. The output string buffer is cleared.
/// @param self The emission context.
void
Mkx_Scribe_Cas_EmissionContext_reset
  (
    Mkx_Scribe_Cas_EmissionContext* self
  );

#endif // MKX_SCRIBE_CAS_EMISSIONCONTEXT_H_INCLUDED
