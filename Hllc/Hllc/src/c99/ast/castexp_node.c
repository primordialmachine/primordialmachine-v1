#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/castexp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"
#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/unexp_node.h"
#undef CC_C99_AST_PRIVATE

static void visit(cc_c99_castexp_node* self)
{
  CC_VISIT(self->type);
  CC_VISIT(self->operand);
}

static void write(cc_c99_castexp_node* self, cc_emit* emit)
{
  // Backup & update state flags.
  cc_emit_state_flags old_state_flags = emit->state_flags;
  emit->state_flags = (emit->state_flags) & ~CC_EMIT_STATE_FLAG_BLOCK;
  emit->state_flags = (emit->state_flags) | CC_EMIT_STATE_FLAG_INLINE;

  cc_emit_write_f(emit, "(");
  cc_emit_write_node(emit, self->type);
  cc_emit_write_f(emit, ")");

  bool parentheses_required = true;
  if (self->operand->kind == CC_C99_NODE_KIND_EXP) {
    if (((cc_c99_exp_node *)self->operand)->kind == CC_C99_EXP_NODE_KIND_UN)
    {
      if (((cc_c99_unexp_node*)self->operand)->operator == CC_C99_UNOP_ADDRESS_OF)
      {
        parentheses_required = false;
      }
    }
    else if (((cc_c99_exp_node *)self->operand)->kind == CC_C99_EXP_NODE_KIND_NAME)
    {
      parentheses_required = false;
    }
  }
  if (parentheses_required) cc_emit_write_f(emit, "(");
  cc_emit_write_node(emit, self->operand);
  if (parentheses_required) cc_emit_write_f(emit, ")");

  // Restore state flags.
  emit->state_flags = old_state_flags;
}

CC_DEFINE_CLASS(cc_c99_castexp_node, cc_c99_exp_node, &visit, NULL, NULL, NULL)

void
cc_c99_castexp_node_construct
  (
    cc_c99_castexp_node* self,
    cc_c99_node* type,
    cc_c99_node* operand
  )
{
  CC_BEGIN_CTOR(cc_c99_castexp_node);
  cc_c99_exp_node_construct((cc_c99_exp_node *)self, CC_C99_EXP_NODE_KIND_CAST);
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *)) & write;
  self->type = type;
  self->operand = operand;
  CC_END_CTOR(cc_c99_castexp_node);
}

cc_c99_castexp_node*
cc_c99_castexp_node_create
  (
    cc_c99_node* type,
    cc_c99_node* operand
  )
{
  cc_c99_castexp_node* self = (cc_c99_castexp_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_castexp_node_get_type)());
  cc_c99_castexp_node_construct(self, type, operand);
  return self;
}
