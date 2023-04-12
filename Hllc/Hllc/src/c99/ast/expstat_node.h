#if !defined(CC_C99_AST_EXPSTAT_NODE_H_INCLUDED)
#define CC_C99_AST_EXPSTAT_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/expstat_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/node.h"

/// @brief An expression statement node.
/// <code>
/// <expression> ';'
/// </code>
CC_DECLARE_CLASS(cc_c99_expstat_node, cc_c99_node);

struct cc_c99_expstat_node
{
  cc_c99_node parent;
  cc_c99_node* expression;
};

cc_c99_expstat_node*
cc_c99_expstat_node_create
  (
    cc_c99_node* expression
  );

#endif // CC_C99_AST_EXPSTAT_NODE_H_INCLUDED
