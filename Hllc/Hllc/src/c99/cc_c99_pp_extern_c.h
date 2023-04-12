#if !defined(CC_C99_PP_EXTERN_C_H_INCLUDED)
#define CC_C99_PP_EXTERN_C_H_INCLUDED

#include "c99/cc_c99_group_node.h"

CC_DECLARE_CLASS(cc_c99_pp_extern_c_node, cc_object)

struct cc_c99_pp_extern_c_node {
  cc_c99_group_node parent;
};

/// Create a node
/// <code>
/// #if defined(__cplusplus)
/// extern "C" {
/// #endif
/// <children>
/// #if defined(__cplusplus)
/// }
/// #endif
/// </code>
cc_c99_pp_extern_c_node* cc_c99_node_create_pp_extern_c_node();

/// @brief Append a node to this extern C node.
/// @param self This extern C node.
/// @param node The node to append to this extern C node.
void cc_c99_pp_extern_c_node_append(cc_c99_pp_extern_c_node* self, cc_c99_node* node);

#endif // CC_C99_PP_EXTERN_C_H_INCLUDED