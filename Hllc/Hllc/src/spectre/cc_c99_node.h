#if !defined(__CC_C99_NODE_H_INCLUDED)
#define __CC_C99_NODE_H_INCLUDED


#include "spectre/cc_emit-protected.h"

#include "c99/ast/node.h"
#include "c99/cc_c99_group_node.h"
#include "c99/cc_c99_pp_include_directive.h"
#include "c99/cc_c99_pp_extern_c.h"
#include "c99/cc_c99_pp_inclusion_guard.h"
#include "c99/cc_c99_struct_declarator_node.h"
#include "c99/cc_c99_struct_declaration_node.h"
#include "c99/cc_c99_struct_definition_node.h"
#include "c99/cc_c99_enum_declarator_node.h"
#include "c99/cc_c99_function_declarator_node.h"
#include "c99/cc_c99_function_definition_node.h"
#include "c99/cc_c99_function_declaration_node.h"
#include "c99/cc_c99_enum_element_declarator_node.h"
#include "c99/cc_c99_param_node.h"
#include "c99/cc_c99_param_list_node.h"
#include "c99/cc_c99_var_declarator_node.h"
#include "c99/cc_c99_typedef_declarator_node.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_types_list_node, cc_object)

struct cc_c99_types_list_node
{
  cc_c99_node parent;
  bool multi_line;
  cc_arraylist* types;
};

/// Create a node
/// @code
/// <type-list> : '(' <type-list-first> ')'
/// <types-list-first> :   <type> <types-list-rest>
///                      | e
/// <types-list-rest> :   ',' <type> <types-list-rest>
///                     : e
/// @endcode
/// @return 
cc_c99_types_list_node* cc_c99_node_create_types_list(bool multi_line);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A single line of text.
/// <code>
/// <text without newlines>
/// </code>
/// Indention is applied.
CC_DECLARE_CLASS(cc_c99_text_line_node, cc_c99_node);

struct cc_c99_text_line_node
{
  cc_c99_node parent;
  cc_cstring* text;
};

/// @param  text The text. Must not contain '\n' or '\r'.
cc_c99_text_line_node*
cc_c99_node_create_text_line
  (
    cc_cstring* text
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Write a node.
/// @param self A pointer to this emit stage.
/// @param node A pointer to the node.
void cc_emit_write_node(cc_emit* self, cc_c99_node* node);

#endif // __CC_C99_NODE_H_INCLUDED__