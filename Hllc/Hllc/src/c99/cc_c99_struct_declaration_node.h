#if !defined(CC_C99_STRUCT_DECLARATION_NODE_H_INCLUDED)
#define CC_C99_STRUCT_DECLARATION_NODE_H_INCLUDED

#include "c99/ast/node.h"
CC_FORWARD_DECLARE_CLASS(cc_c99_struct_declarator_node);

CC_DECLARE_CLASS(cc_c99_struct_declaration_node, cc_object)

struct cc_c99_struct_declaration_node
{
  cc_c99_node parent;
  cc_c99_struct_declarator_node* declarator;
};

/// Create a node.
/// <code>
/// struct_declaration : struct <name> ';'
/// </code>
cc_c99_struct_declaration_node* cc_c99_node_create_struct_declaration(cc_c99_struct_declarator_node *declarator);

#endif // CC_C99_STRUCT_DECLARATION_NODE_H_INCLUDED
