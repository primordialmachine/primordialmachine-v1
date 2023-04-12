#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/nameexp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_nameexp_node* self)
{
  CC_VISIT(self->name);
}

static void write(cc_c99_nameexp_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "%s", self->name->p);
}

CC_DEFINE_CLASS(cc_c99_nameexp_node, cc_c99_exp_node, &visit, NULL, NULL, NULL)

void
cc_c99_nameexp_node_construct
  (
    cc_c99_nameexp_node* self,
    cc_cstring* name
  )
{
  CC_BEGIN_CTOR(cc_c99_nameexp_node);
  cc_c99_exp_node_construct((cc_c99_exp_node *)self, CC_C99_EXP_NODE_KIND_NAME);
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *)) & write;
  self->name = name;
  CC_END_CTOR(cc_c99_nameexp_node);
}

cc_c99_nameexp_node*
cc_c99_nameexp_node_create
  (
    cc_cstring* name
  )
{
  cc_c99_nameexp_node* self = (cc_c99_nameexp_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_nameexp_node_get_type)());
  cc_c99_nameexp_node_construct(self, name);
  return self;
}
