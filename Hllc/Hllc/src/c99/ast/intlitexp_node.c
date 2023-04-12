#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/intlitexp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_intlitexp_node* self)
{
  CC_VISIT(self->literal);
}

static void write(cc_c99_intlitexp_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "%s", self->literal->p);
}

CC_DEFINE_CLASS(cc_c99_intlitexp_node, cc_c99_exp_node, &visit, NULL, NULL, NULL)

void
cc_c99_intlitexp_node_construct
  (
    cc_c99_intlitexp_node *self,
    cc_cstring* literal
  )
{
  CC_BEGIN_CTOR(cc_c99_intlitexp_node);
  cc_c99_exp_node_construct((cc_c99_exp_node *)self, CC_C99_EXP_NODE_KIND_INTLIT);
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *)) & write;
  self->literal = literal;
  CC_END_CTOR(cc_c99_intlitexp_node);
}

cc_c99_intlitexp_node*
cc_c99_intlitexp_node_create
  (
    cc_cstring* literal
  )
{
  cc_c99_intlitexp_node* self = (cc_c99_intlitexp_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_intlitexp_node_get_type)());
  cc_c99_intlitexp_node_construct(self, literal);
  return self;
}
