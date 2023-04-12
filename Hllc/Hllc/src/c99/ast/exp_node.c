#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/exp_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

CC_DEFINE_CLASS(cc_c99_exp_node, cc_object, NULL, NULL, NULL, NULL)

void
cc_c99_exp_node_construct
  (
    cc_c99_exp_node* self,
    cc_c99_exp_node_kind kind
  )
{
  CC_BEGIN_CTOR(cc_c99_exp_node);
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_EXP;
  self->kind = kind;
  CC_END_CTOR(cc_c99_exp_node);
}