#if !defined(CC_C99_TYPEDEF_DECLARATOR_NODE_H_INCLUDED)
#define CC_C99_TYPEDEF_DECLARATOR_NODE_H_INCLUDED

#include "c99/ast/node.h"

/// @code
/// 'typedef' <return type> '(' '*'* <name> ')' <parameter_list> ';'
/// @endcode
/// if the base type is a function type declatator.
/// @code
/// 'typedef' <type> <name> ';'
/// @endcode
/// if the base type is a named type declarator.
/// @code
/// 'typedef' 'struct' <struct name> <struct body>? <name> ';'
/// @endcode
/// if the base type is a struct declarator.
CC_DECLARE_CLASS(cc_c99_typedef_decl_node, cc_c99_node);

struct cc_c99_typedef_decl_node
{
  cc_c99_node parent;
  cc_cstring* name;
  cc_c99_node* declarator;
};

cc_c99_typedef_decl_node*
cc_c99_node_create_typedef_decl
  (
    cc_cstring* name,
    cc_c99_node* declarator
  );

#endif // CC_C99_TYPEDEF_DECLARATOR_NODE_H_INCLUDED