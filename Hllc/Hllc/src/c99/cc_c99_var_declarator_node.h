#if !defined(CC_C99_VAR_DECLARATOR_NODE_H_INCLUDED)
#define CC_C99_VAR_DECLARATOR_NODE_H_INCLUDED

#include "c99/ast/node.h"


CC_DECLARE_CLASS(cc_c99_var_declarator_node, cc_object)

struct cc_c99_var_declarator_node
{
  cc_c99_node parent;
  cc_cstring* name;
  cc_c99_node* type;
  bool is_static;
};

/// Create a node.
/// <code>
/// var_declarator : 'static'? <type> <name> ';'
/// </code>
cc_c99_var_declarator_node* cc_c99_node_create_var_declarator(cc_cstring* name, bool is_static, cc_c99_node* type);

#endif // CC_C99_VAR_DECLARATOR_NODE_H_INCLUDED