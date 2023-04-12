#include "c99/cc_c99_group_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_group_node_visit(cc_c99_group_node* self)
{
  CC_VISIT(self->children);
}

static void write_group_node(cc_c99_group_node* self, cc_emit* emit)
{ 
  for (size_t i = 0, n = cc_arraylist_get_size(self->children); i < n; ++i)
  {
    cc_c99_node *child = (cc_c99_node *)cc_arraylist_get_at(self->children, i);
    cc_emit_write_node(emit, child);
  }
}

CC_DEFINE_CLASS(cc_c99_group_node, cc_c99_node, NULL, NULL, NULL, NULL)

cc_c99_group_node* cc_c99_node_create_group_node()
{
  cc_c99_group_node* self = (cc_c99_group_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_group_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_GROUP;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_group_node;
  self->children = cc_arraylist_create(0);
  return self;
}

void cc_c99_group_node_append(cc_c99_group_node* self, cc_c99_node* node)
{
  cc_arraylist_append(self->children, (cc_object*)node);
}
