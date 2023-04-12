#if !defined(CC_C99_AST_BINEXP_NODE_H_INCLUDED)
#define CC_C99_AST_BINEXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/binexp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/exp_node.h"

typedef enum cc_c99_binop
{
  CC_C99_BINOP_PLUS,
  CC_C99_BINOP_MINUS,
  CC_C99_BINOP_STAR,
  CC_C99_BINOP_SLASH,
  CC_C99_BINOP_ASSIGN,
  CC_C99_BINOP_STRUCTURE_DEREFERENCE,
} cc_c99_binop;

CC_DECLARE_CLASS(cc_c99_binexp_node, cc_object)

struct cc_c99_binexp_node
{
  cc_c99_exp_node parent;
  cc_c99_binop operator;
  cc_c99_node* left_operand;
  cc_c99_node* right_operand;
};

void
cc_c99_binexp_node_construct
  (
    cc_c99_binexp_node* self,
    cc_c99_binop operator,
    cc_c99_node* left_operand,
    cc_c99_node* right_operand
  );

/// Create a node
/// <code>
/// E1 BINOP E2
/// </code>
/// @return 
cc_c99_binexp_node*
cc_c99_binexp_node_create
  (
    cc_c99_binop operator,
    cc_c99_node* left_operand,
    cc_c99_node* right_operand
  );

#endif // CC_C99_AST_BINEXP_NODE_H_INCLUDED
