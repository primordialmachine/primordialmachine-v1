#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/node.h"
#undef CC_C99_AST_PRIVATE

void
cc_c99_node_construct
  (
    cc_c99_node* self,
    cc_c99_node_kind kind
  )
{
  CC_BEGIN_CTOR(cc_c99_node);
  self->kind = kind;
  CC_END_CTOR(cc_c99_node);
}
