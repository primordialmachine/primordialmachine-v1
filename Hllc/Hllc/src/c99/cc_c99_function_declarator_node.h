#if !defined(CC_C99_FUNCTION_DECLARATOR_NODE_H_INCLUDED)
#define CC_C99_FUNCTION_DECLARATOR_NODE_H_INCLUDED

#include "c99/ast/node.h"
CC_FORWARD_DECLARE_CLASS(cc_c99_group_node);
CC_FORWARD_DECLARE_CLASS(cc_c99_params_list_node);

CC_DECLARE_CLASS(cc_c99_function_declarator_node, cc_object)

struct cc_c99_function_declarator_node
{
  cc_c99_node parent;
  cc_c99_node* result_type;
  cc_cstring* name;
  cc_c99_params_list_node* params;
  /// @brief Pointer to a group node or a null pointer.
  cc_c99_group_node* body;
  bool is_static;
};

/// Create a node
/// <code>
/// function_declarator : 'static'? <result_type_declarator> <name> <parameter_list_declarator>
/// </code>
cc_c99_function_declarator_node* cc_c99_node_create_function_declarator(cc_cstring* name, bool is_static, cc_c99_node* result_type, cc_c99_params_list_node *params);

#endif // CC_C99_FUNCTION_DECLARATOR_NODE_H_INCLUDED
