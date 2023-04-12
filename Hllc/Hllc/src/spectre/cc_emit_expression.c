#include "spectre/cc_emit_expression.h"

#include <stdio.h>
#include "cc_c99_node.h"
#include "c99/ast/_include.h"

cc_c99_node* cc_c99_create_expression(cc_tree* e)
{
  switch (cc_t_get_kind(e))
  {
  case CC_TT_BINARY_MINUS_EXPRESSION:
    return
      (cc_c99_node *)
        cc_c99_binexp_node_create
          (
            CC_C99_BINOP_MINUS,
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->left_operand),
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->right_operand)
          );
  case CC_TT_BINARY_PLUS_EXPRESSION:
    return
      (cc_c99_node*)
        cc_c99_binexp_node_create
          (
            CC_C99_BINOP_PLUS,
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->left_operand),
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->right_operand)
          );
  case CC_TT_BINARY_STAR_EXPRESSION:
    return
      (cc_c99_node*)
        cc_c99_binexp_node_create
          (
            CC_C99_BINOP_STAR,
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->left_operand),
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->right_operand)
          );
  case CC_TT_BINARY_SLASH_EXPRESSION:
    return
      (cc_c99_node*)
        cc_c99_binexp_node_create
          (
            CC_C99_BINOP_SLASH,
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->left_operand),
            cc_c99_create_expression(cc_tree_to_binary_expression(e)->right_operand)
          );
  case CC_TT_UNARY_MINUS_EXPRESSION:
    return
        (cc_c99_node*)
          cc_c99_unexp_node_create
            (
              CC_C99_UNOP_MINUS,
              cc_c99_create_expression(cc_tree_to_unary_expression(e)->operand)
            );
  case CC_TT_UNARY_PLUS_EXPRESSION:
    return
      (cc_c99_node*)
        cc_c99_unexp_node_create
          (
            CC_C99_UNOP_PLUS,
            cc_c99_create_expression(cc_tree_to_unary_expression(e)->operand)
          );
  case CC_TT_STRING_EXPRESSION:
    return
      (cc_c99_node*)
        cc_c99_stringlitexp_node_create
          (
            cc_tree_to_literal_expression(e)->literal
          );
  case CC_TT_INTEGER_EXPRESSION:
    return
      (cc_c99_node*)
        cc_c99_intlitexp_node_create
          (
            cc_tree_to_literal_expression(e)->literal
          );
  default:
  {
    fprintf(stderr, "<internal error>");
    cc_error(CC_EINVAL);
  } break;
  };
}
