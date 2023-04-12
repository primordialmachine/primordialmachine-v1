#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/callexp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_callexp_node* self)
{
  CC_VISIT(self->exp);
  CC_VISIT(self->arg_exps);
}

static void write(cc_c99_callexp_node* self, cc_emit* emit)
{
  // Backup & update state flags.
  cc_emit_state_flags old_state_flags = emit->state_flags;
  emit->state_flags = (emit->state_flags) & ~CC_EMIT_STATE_FLAG_BLOCK;
  emit->state_flags = (emit->state_flags) | CC_EMIT_STATE_FLAG_INLINE;

  cc_emit_write_node(emit, self->exp);

  cc_emit_write_f(emit, "(");
  size_t n = cc_arraylist_get_size(self->arg_exps);
  if (n > 0)
  {
    size_t i = 0;
    cc_c99_node* argument_expression = (cc_c99_node*)cc_arraylist_get_at(self->arg_exps, i);
    cc_emit_write_node(emit, argument_expression);
    i++;
    for (; i < n; ++i)
    {
      argument_expression = (cc_c99_node*)cc_arraylist_get_at(self->arg_exps, i);
      cc_emit_write_f(emit, ", ");
      cc_emit_write_node(emit, argument_expression);
    }
  }
  cc_emit_write_f(emit, ")");
  // Restore state flags.
  emit->state_flags = old_state_flags;
}

CC_DEFINE_CLASS(cc_c99_callexp_node, cc_c99_exp_node, &visit, NULL, NULL, NULL)

void
cc_c99_callexp_node_construct
  (
    cc_c99_callexp_node *self,
    cc_c99_node* exp,
    cc_arraylist* arg_exps
  )
{
  CC_BEGIN_CTOR(cc_c99_callexp_node);
  cc_c99_exp_node_construct((cc_c99_exp_node *)self, CC_C99_EXP_NODE_KIND_CALL);
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *)) & write;
  self->exp = exp;
  self->arg_exps = arg_exps;
  CC_END_CTOR(cc_c99_callexp_node);
}

cc_c99_callexp_node*
cc_c99_callexp_node_create
  (
    cc_c99_node* exp,
    cc_arraylist *arg_exps
  )
{
  cc_c99_callexp_node* self = (cc_c99_callexp_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_callexp_node_get_type)());
  cc_c99_callexp_node_construct(self, exp, arg_exps);
  return self;
}
