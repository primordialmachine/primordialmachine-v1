#if !defined(CC_C99_AST_CALLEXP_NODE_H_INCLUDED)
#define CC_C99_AST_CALLEXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/callexp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/exp_node.h"

CC_DECLARE_CLASS(cc_c99_callexp_node, cc_object)

struct cc_c99_callexp_node
{
  cc_c99_exp_node parent;
  cc_c99_node* exp;
  cc_arraylist* arg_exps;
};

void
cc_c99_callexp_node_construct
  (
    cc_c99_callexp_node* self,
    cc_c99_node* exp,
    cc_arraylist* arg_exps
  );

/// Create a node
/// <code>
/// <expression> <argument-expressions>
/// <argument-expressions> : '(' <argument-expressions-1> ')'
/// <argument-expressions-1> : <argument-expression> <argument-expressions-2>
///                          | e
/// <argument-expressions-2> : ',' <argument-expression> <argument-expressions-2>
///                          | e
/// </code>
cc_c99_callexp_node*
cc_c99_callexp_node_create
  (
    cc_c99_node* exp,
    cc_arraylist* arg_exps
  );

#endif // CC_C99_AST_CALLEXP_NODE_H_INCLUDED
