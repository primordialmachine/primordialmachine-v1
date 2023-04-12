#if !defined(CC_C99_FUNCTION_DEFINITION_NODE_H_INCLUDED)
#define CC_C99_FUNCTION_DEFINITION_NODE_H_INCLUDED

#include "c99/ast/node.h"
CC_FORWARD_DECLARE_CLASS(cc_c99_function_declarator_node);

CC_DECLARE_CLASS(cc_c99_function_definition_node, cc_object)

struct cc_c99_function_definition_node
{
  cc_c99_node parent;
  cc_c99_function_declarator_node* declarator;
};

/// Create a node
/// @code
/// <newline>
/// <static>? <result_type> <name> <parameter_list> <body>
/// <newline>
/// @endcode
cc_c99_function_definition_node* cc_c99_node_create_function_definition(cc_c99_function_declarator_node* declarator);

#endif // CC_C99_FUNCTION_DEFINITION_NODE_H_INCLUDED
