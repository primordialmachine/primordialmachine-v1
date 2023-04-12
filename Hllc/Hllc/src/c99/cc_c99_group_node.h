#if !defined(CC_C99_GROUP_NODE_H_INCLUDED)
#define CC_C99_GROUP_NODE_H_INCLUDED

#include "c99/ast/node.h"

CC_DECLARE_CLASS(cc_c99_group_node, cc_object)

struct cc_c99_group_node
{
  cc_c99_node parent;
  cc_arraylist* children;
};

/// Create a node
/// <code>
/// <children>
/// </code>
cc_c99_group_node* cc_c99_node_create_group_node();

/// @brief Append a node to this group node.
/// @param self This group node.
/// @param node The node to append to this group node.
void cc_c99_group_node_append(cc_c99_group_node* self, cc_c99_node *node);

#endif // CC_C99_GROUP_NODE_H_INCLUDED
