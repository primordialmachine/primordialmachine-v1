#if !defined(CC_C99_AST_IfSTAT_NODE_H_INCLUDED)
#define CC_C99_AST_IfSTAT_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/ifstat_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/node.h"

/// @brief An if statement node.
/// <code>
/// 'if' '(' <expression> ')'
///   <statement>
/// </code>
CC_DECLARE_CLASS(cc_c99_ifstat_node, cc_c99_node);

struct cc_c99_ifstat_node
{
  cc_c99_node parent;
  cc_c99_node* condition;
  cc_c99_node* statement;
};

cc_c99_ifstat_node*
cc_c99_ifstat_node_create
  (
    cc_c99_node* condition,
    cc_c99_node* statement
  );

#endif // CC_C99_AST_IFSTAT_NODE_H_INCLUDED
