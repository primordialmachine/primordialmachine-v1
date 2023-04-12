#if !defined(CC_C99_PP_INCLUSION_GUARD_H_INCLUDED)
#define CC_C99_PP_INCLUSION_GUARD_H_INCLUDED

#include "c99/cc_c99_group_node.h"

CC_DECLARE_CLASS(cc_c99_pp_inclusion_guard_node, cc_object)

struct cc_c99_pp_inclusion_guard_node
{
  cc_c99_group_node parent;
  cc_cstring* name;
};

/// Create a node
/// <code>
/// #if !defined(NAME)
/// #define NAME
/// <children>
/// #endif // NAME
/// </code>
/// @return 
cc_c99_pp_inclusion_guard_node* cc_c99_node_create_pp_inclusion_guard(cc_cstring *name);

void cc_c99_pp_inclusion_guard_node_append(cc_c99_pp_inclusion_guard_node* self, cc_c99_node* node);

#endif // CC_C99_PP_INCLUSION_GUARD_H_INCLUDED