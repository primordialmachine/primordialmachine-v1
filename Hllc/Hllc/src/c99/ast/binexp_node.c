#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/binexp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_binexp_node* self)
{
  CC_VISIT(self->left_operand);
  CC_VISIT(self->right_operand);
}

static void write(cc_c99_binexp_node* self, cc_emit* emit)
{
  cc_emit_write_node(emit, self->left_operand);
  switch (self->operator)
  {
  case CC_C99_BINOP_PLUS:
    cc_emit_write_f(emit, " + ");
    break;
  case CC_C99_BINOP_MINUS:
    cc_emit_write_f(emit, " - ");
    break;
  case CC_C99_BINOP_STAR:
    cc_emit_write_f(emit, " * ");
    break;
  case CC_C99_BINOP_SLASH:
    cc_emit_write_f(emit, " / ");
    break;
  case CC_C99_BINOP_ASSIGN:
    cc_emit_write_f(emit, " = ");
    break;
  case CC_C99_BINOP_STRUCTURE_DEREFERENCE:
    cc_emit_write_f(emit, "->");
    break;
  default:
    cc_error(CC_EINVAL);
  };
  cc_emit_write_node(emit, self->right_operand);
}

CC_DEFINE_CLASS(cc_c99_binexp_node, cc_c99_exp_node, &visit, NULL, NULL, NULL)

void
cc_c99_binexp_node_construct
  (
    cc_c99_binexp_node *self,
    cc_c99_binop operator,
    cc_c99_node* left_operand,
    cc_c99_node* right_operand
  )
{
  CC_BEGIN_CTOR(cc_c99_binexp_node);
  cc_c99_exp_node_construct((cc_c99_exp_node *)self, CC_C99_EXP_NODE_KIND_BIN);
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *)) & write;
  self->operator = operator;
  self->left_operand = left_operand;
  self->right_operand = right_operand;
  CC_END_CTOR(cc_c99_binexp_node);
}

cc_c99_binexp_node*
cc_c99_binexp_node_create
  (
    cc_c99_binop operator,
    cc_c99_node* left_operand,
    cc_c99_node* right_operand
  )
{
  cc_c99_binexp_node* self = (cc_c99_binexp_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_binexp_node_get_type)());
  cc_c99_binexp_node_construct(self, operator, left_operand, right_operand);
  return self;
}
