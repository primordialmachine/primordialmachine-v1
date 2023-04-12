#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/ifstat_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_ifstat_node* self)
{
  CC_VISIT(self->condition);
  CC_VISIT(self->statement);
}

static void write(cc_c99_ifstat_node* self, cc_emit* emit)
{
  cc_emit_write_indent(emit, emit->indent);

  cc_emit_write_f(emit, "if");
  cc_emit_write_f(emit, " ");
  cc_emit_write_f(emit, "(");
  cc_emit_write_node(emit, self->condition);
  cc_emit_write_f(emit, ")");
  cc_emit_write_f(emit, "\n");
  if (self->statement->kind == CC_C99_NODE_KIND_BLOCK_STATEMENT)
  {
    cc_emit_write_node(emit, self->statement);
  }
  else
  {
    emit->indent += 1;
    cc_emit_write_node(emit, self->statement);
    emit->indent -= 1;
  }
}

CC_DEFINE_CLASS(cc_c99_ifstat_node, cc_c99_node, &visit, NULL, NULL, NULL)

cc_c99_ifstat_node* cc_c99_ifstat_node_create(cc_c99_node* condition, cc_c99_node* statement)
{
  cc_c99_ifstat_node* self = (cc_c99_ifstat_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_ifstat_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_IF_STATEMENT;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write;
  self->condition = condition;
  self->statement = statement;
  return self;
}
