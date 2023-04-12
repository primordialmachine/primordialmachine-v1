#if !defined(CC_C99_AST_NODE_H_INCLUDED)
#define CC_C99_AST_NODE_H_INCLUDED

#include "cc_context.h"

/// @brief Enumeration of the kinds of nodes.
typedef enum cc_c99_node_kind
{
  /// @todo Rename to node list.
  CC_C99_NODE_KIND_GROUP,

  /// @brief A single line of text.
  /// The text must not contain newlines and is printed verbatim.
  /// Margins are applied.
  CC_C99_NODE_KIND_TEXT_LINE,

  /// <code>
  /// #if !defined(<name>)
  /// #define <name>
  /// <children>
  /// #endif
  /// </code>
  CC_C99_NODE_KIND_PP_INCLUSION_GUARD,

  // Preprocessor include directive
  // @code
  // #include "<path>"
  // @endcode
  // where @code{<path>} is the path of the file to be included.
  CC_C99_NODE_KIND_PP_INCLUDE_DIRECTIVE,
  CC_C99_NODE_KIND_EXTERN_C,          // C preprocessor/C

  CC_C99_NODE_KIND_EXP, // expression

  CC_C99_NODE_KIND_POINTER_TYPE_DECLARATOR,
  CC_C99_NODE_KIND_NAMED_TYPE_DECLARATOR,
  CC_C99_NODE_KIND_FUNCTION_TYPE_DECLARATOR,

  CC_C99_NODE_KIND_PARAM,
  CC_C99_NODE_KIND_PARAM_LIST,
  CC_C99_NODE_KIND_TYPE_LIST,

  CC_C99_NODE_KIND_FUNCTION_DECLARATOR,
  CC_C99_NODE_KIND_STRUCT_DECLARATOR,
  CC_C99_NODE_KIND_ENUM_DECLARATOR,
  CC_C99_NODE_KIND_ENUM_ELEMENT_DECLARATOR,
  CC_C99_NODE_KIND_VAR_DECLARATOR,
  CC_C99_NODE_KIND_TYPEDEF_DECL,

  // Declaration of a function.
  CC_C99_NODE_KIND_FUNCTION_DECLARATION,
  // Definition of a function.
  CC_C99_NODE_KIND_FUNCTION_DEFINITION,
  // Declaration of a struct.
  CC_C99_NODE_KIND_STRUCT_DECLARATION,
  // Definition of a struct.
  CC_C99_NODE_KIND_STRUCT_DEFINITION,

  CC_C99_NODE_KIND_BLOCK_STATEMENT,      // statement
  CC_C99_NODE_KIND_RETURN_STATEMENT,     // statement
  CC_C99_NODE_KIND_EXPRESSION_STATEMENT, // statement
  CC_C99_NODE_KIND_IF_STATEMENT,         // statement

} cc_c99_node_kind;

CC_DECLARE_CLASS(cc_c99_node, cc_object)

struct cc_c99_node
{
  cc_object parent;
  cc_c99_node_kind kind;
  void (*write)(cc_c99_node* self, cc_emit* emit);
};

void
cc_c99_node_construct
  (
    cc_c99_node* self,
    cc_c99_node_kind kind
  );

#endif // CC_C99_AST_NODE_H_INCLUDED
