#if !defined(CC_C99_PARAM_NODE_H_INCLUDED)
#define CC_C99_PARAM_NODE_H_INCLUDED

#include "spectre/cc_c99_node.h"

CC_DECLARE_CLASS(cc_c99_param_node, cc_object)

struct cc_c99_param_node {
  cc_c99_node parent;
  /// @brief The name.
  cc_cstring* name;
  /// @brief The declarator.
  cc_c99_node* type;
  /// @brief If the name of the parameter should be emitted.
  bool with_name;
  /// @brief If the parameter is an "out" parameter.
  bool is_out;
};

/// Create a node param node.
/// Let @code{<NAME>} be the name specified by @a name.
/// Let @code{<TYPE>} be the type specified by @a type.
/// Let @code{<WITH-NAME>} be the boolean value specifed by @a with_name.
/// Let @code{<IS-OUT>} be the boolean value specified by @a is_out.
/// Then
/// @code
/// <type> :=   make_pointer(<TYPE>) if <IS-OUT> = true
///           | <TYPE>               if <IS-OUT> = false
/// <param> :=   <type> <name> if <WITH-NAME> = true
///            | <type>        if <WITH-NAME> = false
/// @endcode
cc_c99_param_node*
cc_c99_node_create_param
  (
    cc_cstring* name,
    cc_c99_node* type,
    bool with_name,
    bool is_out
  );

#endif // CC_C99_PARAM_NODE_H_INCLUDED
