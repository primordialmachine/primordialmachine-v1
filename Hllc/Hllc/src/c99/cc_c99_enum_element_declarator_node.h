#if !defined(CC_C99_ENUM_ELEMENT_DECLARATOR_NODE_H_INCLUDED)
#define CC_C99_ENUM_ELEMENT_DECLARATOR_NODE_H_INCLUDED

#include "c99/ast/node.h"

CC_DECLARE_CLASS(cc_c99_enum_element_declarator_node, cc_object)

struct cc_c99_enum_element_declarator_node
{
  cc_c99_node parent;
  cc_cstring* name;
  cc_c99_node* initializer;
};

/// Create a node.
/// <code>
/// enum_element_declatator : <name> ('=' <initializer>)? ','
/// </code>
cc_c99_enum_element_declarator_node* cc_c99_node_create_enum_element_declarator(cc_cstring* name, cc_c99_node* initializer);

#endif // CC_C99_ENUM_ELEMENT_DECLARATOR_NODE_H_INCLUDED
