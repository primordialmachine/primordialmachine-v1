#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/unexp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_unexp_node* self)
{
  CC_VISIT(self->operand);
}

static bool is_name_exp(cc_c99_node const* self) {
  if (self->kind == CC_C99_NODE_KIND_EXP) {
    return ((cc_c99_exp_node*)self)->kind == CC_C99_EXP_NODE_KIND_NAME;
  }
  return false;
}

static bool is_call_exp(cc_c99_node const* self) {
  if (self->kind == CC_C99_NODE_KIND_EXP) {
    return ((cc_c99_exp_node*)self)->kind == CC_C99_EXP_NODE_KIND_CALL;
  }
  return false;
}

static void write(cc_c99_unexp_node* self, cc_emit* emit)
{
  switch (self->operator)
  {
  case CC_C99_UNOP_PLUS:
  {
    cc_emit_write_f(emit, "+");
    if (is_name_exp(self->operand))
    {
      // We can omit the parentheses here.
      cc_emit_write_node(emit, self->operand);
    }
    else
    {
      cc_emit_write_f(emit, "(");
      cc_emit_write_node(emit, self->operand);
      cc_emit_write_f(emit, ")");
    }
  } break;
  case CC_C99_UNOP_MINUS:
  {
    cc_emit_write_f(emit, "-");
    if (is_name_exp(self->operand))
    {
      // We can omit the parentheses here.
      cc_emit_write_node(emit, self->operand);
    }
    else
    {
      cc_emit_write_f(emit, "(");
      cc_emit_write_node(emit, self->operand);
      cc_emit_write_f(emit, ")");
    }
  } break;
  case CC_C99_UNOP_ADDRESS_OF:
  {
    cc_emit_write_f(emit, "&");
    if (is_name_exp(self->operand))
    {
      // We can omit the parentheses here.
      cc_emit_write_node(emit, self->operand);
    }
    else
    {
      cc_emit_write_f(emit, "(");
      cc_emit_write_node(emit, self->operand);
      cc_emit_write_f(emit, ")");
    }
  } break;
  case CC_C99_UNOP_NOT:
  {
    cc_emit_write_f(emit, "!");
    if (is_name_exp(self->operand) || is_call_exp(self->operand))
    {
      // We can omit the parentheses here.
      cc_emit_write_node(emit, self->operand);
    }
    else
    {
      cc_emit_write_f(emit, "(");
      cc_emit_write_node(emit, self->operand);
      cc_emit_write_f(emit, ")");
    }
  } break;
  case CC_C99_UNOP_GROUP:
  {
    if (is_name_exp(self->operand))
    {
      // We can omit the parentheses here.
      cc_emit_write_node(emit, self->operand);
    }
    else
    {
      cc_emit_write_f(emit, "(");
      cc_emit_write_node(emit, self->operand);
      cc_emit_write_f(emit, ")");
    }
  } break;
  default:
    cc_error(CC_EINVAL);
  };

}

CC_DEFINE_CLASS(cc_c99_unexp_node, cc_c99_exp_node, &visit, NULL, NULL, NULL)

void
cc_c99_unexp_node_construct
  (
    cc_c99_unexp_node* self,
    cc_c99_unop operator,
    cc_c99_node* operand
  )
{
  CC_BEGIN_CTOR(cc_c99_unexp_node);
  cc_c99_exp_node_construct((cc_c99_exp_node *)self, CC_C99_EXP_NODE_KIND_UN);
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *)) & write;
  self->operator = operator;
  self->operand = operand;
  CC_END_CTOR(cc_c99_unexp_node);
}

cc_c99_unexp_node*
cc_c99_unexp_node_create
  (
    cc_c99_unop operator,
    cc_c99_node* operand
  )
{
  cc_c99_unexp_node* self = (cc_c99_unexp_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_unexp_node_get_type)());
  cc_c99_unexp_node_construct(self, operator, operand);
  return self;
}
