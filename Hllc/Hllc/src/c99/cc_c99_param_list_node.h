#if !defined(CC_C99_PARAM_LIST_NODE_H_INCLUDED)
#define CC_C99_PARAM_LIST_NODE_H_INCLUDED

#include "c99/ast/node.h"
CC_FORWARD_DECLARE_CLASS(cc_c99_types_list_node)

CC_DECLARE_CLASS(cc_c99_params_list_node, cc_object)

struct cc_c99_params_list_node
{
  cc_c99_node parent;
  bool multi_line;
  cc_arraylist* params;
};

/// Create a node
/// @code
/// <params-list> : '(' <params-list-first> ')'
/// <params-list-first> :   <param> <params-list-rest>
///                       | e
/// <params-list_rest> :   ',' <param> <params-list-rest>
///                      | e
/// @endcode
/// @return 
cc_c99_params_list_node* cc_c99_node_create_params_list(bool multi_line);

/// @brief Convert this params list into a params type list.
/// @param self This params list.
/// @return The params type list.
cc_c99_types_list_node* cc_c99_params_list_to_params_type_list(cc_c99_params_list_node* self, bool multi_line);

#endif // CC_C99_PARAM_LIST_NODE_H_INCLUDED