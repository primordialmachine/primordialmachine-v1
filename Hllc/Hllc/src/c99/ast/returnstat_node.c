#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/returnstat_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_returnstat_node* self)
{
  CC_VISIT(self->expression);
}

static void write(cc_c99_returnstat_node* self, cc_emit* emit)
{
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "return");
  cc_emit_write_f(emit, " ");
  cc_emit_write_node(emit, self->expression);
  cc_emit_write_f(emit, ";\n");
}

CC_DEFINE_CLASS(cc_c99_returnstat_node, cc_c99_node, &visit, NULL, NULL, NULL)

cc_c99_returnstat_node* cc_c99_returnstat_node_create(cc_c99_node* expression)
{
  cc_c99_returnstat_node* self = (cc_c99_returnstat_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_returnstat_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_RETURN_STATEMENT;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write;
  self->expression = expression;
  return self;
}
