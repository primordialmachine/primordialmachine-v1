#if !defined(CC_C99_AST_NAMEEXP_NODE_H_INCLUDED)
#define CC_C99_AST_NAMEEXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/nameexp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/exp_node.h"

CC_DECLARE_CLASS(cc_c99_nameexp_node, cc_c99_exp_node)

struct cc_c99_nameexp_node
{
  cc_c99_exp_node parent;
  cc_cstring* name;
};

void
cc_c99_nameexp_node_construct
  (
    cc_c99_nameexp_node *self,
    cc_cstring *name
  );

/// Create a node
/// @code
/// <NAME>
/// @endcode
/// @return 
cc_c99_nameexp_node*
cc_c99_nameexp_node_create
  (
    cc_cstring* name
  );

#endif // CC_C99_AST_NAMEEXP_NODE_H_INCLUDED
