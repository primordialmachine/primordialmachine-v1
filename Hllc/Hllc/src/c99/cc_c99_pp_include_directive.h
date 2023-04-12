#if !defined(CC_C99_PP_INCLUDE_DIRECTIVE_H_INCLUDED)
#define CC_C99_PP_INCLUDE_DIRECTIVE_H_INCLUDED

#include "c99/ast/node.h"

CC_DECLARE_CLASS(cc_c99_pp_include_directive_node, cc_object)

struct cc_c99_pp_include_directive_node {
  cc_c99_node parent;
  cc_cstring* include;
};

/// Create a node
/// @code
/// #include "<include>"
/// <children>
/// @endcode
/// where @code{<include>} is the specified include path. 
/// @return 
cc_c99_pp_include_directive_node*
cc_c99_node_create_pp_include_directive
  (
    cc_cstring* include
  );

#endif // CC_C99_PP_INCLUDE_DIRECTIVE_H_INCLUDED
