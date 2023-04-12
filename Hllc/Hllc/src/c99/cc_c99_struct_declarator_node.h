#if !defined(CC_C99_STRUCT_DECLARATOR_NODE_H_INCLUDED)
#define CC_C99_STRUCT_DECLARATOR_NODE_H_INCLUDED

#include "c99/ast/node.h"

CC_DECLARE_CLASS(cc_c99_struct_declarator_node, cc_object)

struct cc_c99_struct_declarator_node {
  cc_c99_node parent;
  /// @brief The name of the struct.
  cc_cstring* name;
  /// @brief The body of the struct (possibly empty list of members) or null.
  cc_arraylist* body;
};

/// Create a node.
/// <code>
/// struct_declarator : struct <name> <body>? ';'
/// </code>
cc_c99_struct_declarator_node*
cc_c99_node_create_struct_declarator
  (
    cc_cstring* name
  );

#endif // CC_C99_STRUCT_DECLARATOR_NODE_H_INCLUDED
