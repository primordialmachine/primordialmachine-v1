#if !defined(CC_C99_STRINGLITEXP_NODE_H_INCLUDED)
#define CC_C99_STRINGLITEXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/stringlitexp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/exp_node.h"

CC_DECLARE_CLASS(cc_c99_stringlitexp_node, cc_c99_exp_node)

struct cc_c99_stringlitexp_node
{
  cc_c99_exp_node parent;
  cc_cstring* literal;
};

void
cc_c99_stringlitexp_node_construct
  (
    cc_c99_stringlitexp_node* self,
    cc_cstring* literal
  );

/// Create a node
/// <code>
/// "LITERAL"
/// </code>
/// @return 
cc_c99_stringlitexp_node*
cc_c99_stringlitexp_node_create
  (
    cc_cstring* literal
  );

#endif // CC_C99_STRINGLITEXP_NODE_H_INCLUDED
