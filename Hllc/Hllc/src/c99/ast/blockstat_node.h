#if !defined(CC_C99_BLOCKSTAT_NODE_H_INCLUDED)
#define CC_C99_BLOCKSTAT_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/blockstat_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/node.h"

/// @brief A block statement node.
/// <code>
/// '{'
///   <statement>* 
/// '}'
/// </code>
CC_DECLARE_CLASS(cc_c99_blockstat_node, cc_c99_node);

struct cc_c99_blockstat_node
{
  cc_c99_node parent;
  cc_arraylist* stats;
};

cc_c99_blockstat_node*
cc_c99_blockstat_node_create
  (
  );

void
cc_c99_blockstat_node_append
  (
    cc_c99_blockstat_node* self,
    cc_c99_node* child
  );

#endif // CC_C99_BLOCKSTAT_NODE_H_INCLUDED
