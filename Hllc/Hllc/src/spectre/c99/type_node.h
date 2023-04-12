#if !defined(CC_C99_TYPE_NODE_H_INCLUDED)
#define CC_C99_TYPE_NODE_H_INCLUDED

#include "c99/ast/node.h"
CC_FORWARD_DECLARE_CLASS(cc_c99_function_declarator_node)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_named_type_declarator_node, cc_object)

struct cc_c99_named_type_declarator_node
{
  cc_c99_node parent;
  /// @brief The name.
  cc_cstring* name;
};

/// Create a node
/// <code>
/// <NAME>
/// </code>
/// @return 
cc_c99_named_type_declarator_node* cc_c99_node_create_named_type_declarator(cc_cstring *name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_pointer_type_declarator_node, cc_object)

struct cc_c99_pointer_type_declarator_node
{
  cc_c99_node parent;
  /// @brief The inner type declarator.
  cc_c99_node* inner;
};

/// @brief
/// Create one of the following nodes:
/// -
/// <code>
/// <INNER>'*'
/// </code>
/// if the the innermost type is a named type.
/// -
/// <code>
/// <INNERMOST RESULT> ('*' <INNER>)<INNERMOST PARAMS>
/// </code>
/// îf the innermost type is a function type declarator.
/// @param inner The inner type. Must be a pointer type declarator, named type declarator, or function type declarator.
cc_c99_pointer_type_declarator_node* cc_c99_node_create_pointer_type_declarator(cc_c99_node* inner);

/// @brief Get the innermost type.
/// @param self This pointer declarator node.
/// @param count Pointer to variable receiving the number of pointer levels.
/// @return The innermost type.
cc_c99_node* cc_c99_pointer_type_declarator_get_base(cc_c99_pointer_type_declarator_node* self, size_t *count);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_function_type_declarator_node, cc_object)

struct cc_c99_function_type_declarator_node
{
  cc_c99_node parent;
  cc_c99_function_declarator_node* declarator;
};

/// @brief Create a function type declarator.
/// @param declarator The function declarator.
/// @warning CAN ONLY BE EMITTED AS THE INNER TYPE OF A POINTER TYPE DECLARATOR.
cc_c99_function_type_declarator_node* cc_c99_node_create_function_type_declarator(cc_c99_function_declarator_node* declarator);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // CC_C99_TYPE_NODE_H_INCLUDED
