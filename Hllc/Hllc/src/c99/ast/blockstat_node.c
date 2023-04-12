#define CC_C99_AST_PRIVATE (1)
#include "c99/ast/blockstat_node.h"
#undef CC_C99_AST_PRIVATE

#include "spectre/cc_c99_node.h"

static void visit(cc_c99_blockstat_node* self)
{
  CC_VISIT(self->stats);
}

static void write(cc_c99_blockstat_node* self, cc_emit* emit)
{
  cc_emit_write_indent(emit, emit->indent);
  
  // enter block
  cc_emit_write_f(emit, "{");
  cc_emit_write_f(emit, "\n");
  emit->indent += 1;
  
  for (size_t i = 0, n = cc_arraylist_get_size(self->stats); i < n; ++i)
  {
    cc_c99_node* stat = (cc_c99_node *)cc_arraylist_get_at(self->stats, i);
    cc_emit_write_node(emit, stat);
  }

  // leave block
  emit->indent -= 1;
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "}");
  cc_emit_write_f(emit, "\n");
}

CC_DEFINE_CLASS(cc_c99_blockstat_node, cc_c99_node, &visit, NULL, NULL, NULL)

cc_c99_blockstat_node* cc_c99_blockstat_node_create()
{
  cc_c99_blockstat_node* self = (cc_c99_blockstat_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_blockstat_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_BLOCK_STATEMENT;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write;
  self->stats = cc_arraylist_create(0);
  return self;
}

void cc_c99_blockstat_node_append(cc_c99_blockstat_node* self, cc_c99_node* child)
{
  cc_arraylist_append(self->stats, (cc_object*)child);
}
