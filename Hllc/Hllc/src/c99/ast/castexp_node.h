#if !defined(CC_C99_AST_CASTEXP_NODE_H_INCLUDED)
#define CC_C99_AST_CASTEXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/castexp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/exp_node.h"

CC_DECLARE_CLASS(cc_c99_castexp_node, cc_object)

struct cc_c99_castexp_node
{
  cc_c99_exp_node parent;
  cc_c99_node* type;
  cc_c99_node* operand;
};

void
cc_c99_castexp_node_construct
  (
    cc_c99_castexp_node* self,
    cc_c99_node* type,
    cc_c99_node* operand
  );

/// Create a node
/// <code>
/// ((T)(E))
/// </code>
/// @remark Parentheses should be created CC_C99_UNARY_OPERATOR_GROUP.
cc_c99_castexp_node*
cc_c99_castexp_node_create
  (
    cc_c99_node* type,
    cc_c99_node* operand
  );

#endif // CC_C99_AST_CASTEXP_NODE_H_INCLUDED
