#if !defined(CC_C99_AST_UNEXP_NODE_H_INCLUDED)
#define CC_C99_AST_UNEXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/unexp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/exp_node.h"

typedef enum cc_c99_unop
{
  CC_C99_UNOP_PLUS,
  CC_C99_UNOP_MINUS,
  CC_C99_UNOP_ADDRESS_OF,
  CC_C99_UNOP_GROUP,
  CC_C99_UNOP_NOT,
} cc_c99_unop;

CC_DECLARE_CLASS(cc_c99_unexp_node, cc_c99_exp_node)

struct cc_c99_unexp_node
{
  cc_c99_exp_node parent;
  cc_c99_unop operator;
  cc_c99_node* operand;
};

void
cc_c99_unexp_node_construct
  (
    cc_c99_unexp_node *self,
    cc_c99_unop operator,
    cc_c99_node* operand
  );

/// Create a node
/// <code>
/// UNOP E
/// </code>
/// @return 
cc_c99_unexp_node*
cc_c99_unexp_node_create
  (
    cc_c99_unop operator,
    cc_c99_node* operand
  );

#endif // CC_C99_UNEXP_NODE_H_INCLUDED
