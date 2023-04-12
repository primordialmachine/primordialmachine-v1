#include "c99/cc_c99_pp_extern_c.h"

#include "spectre/cc_c99_node.h"

static void write_extern_c(cc_c99_pp_extern_c_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "\n");
  cc_emit_write_f(emit, "#ifdef __cplusplus\n");
  cc_emit_write_f(emit, "extern \"C\" {\n");
  cc_emit_write_f(emit, "#endif\n");
  cc_emit_write_f(emit, "\n");

  for (size_t i = cc_arraylist_get_size(((cc_c99_group_node*)self)->children); i > 0; --i)
  {
    cc_c99_node* child = (cc_c99_node*)cc_arraylist_get_at(((cc_c99_group_node*)self)->children, i - 1);
    cc_emit_write_node(emit, child);
  }

  cc_emit_write_f(emit, "\n");
  cc_emit_write_f(emit, "#ifdef __cplusplus\n");
  cc_emit_write_f(emit, "}\n");
  cc_emit_write_f(emit, "#endif\n");
}

CC_DEFINE_CLASS(cc_c99_pp_extern_c_node, cc_c99_group_node, NULL, NULL, NULL, NULL)

cc_c99_pp_extern_c_node* cc_c99_node_create_pp_extern_c_node()
{
  cc_c99_pp_extern_c_node*self = (cc_c99_pp_extern_c_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_pp_extern_c_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_EXTERN_C;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*))&write_extern_c;
  ((cc_c99_group_node*)self)->children = cc_arraylist_create(0);
  return self;
}

void cc_c99_pp_extern_c_node_append(cc_c99_pp_extern_c_node* self, cc_c99_node* node)
{
  cc_c99_group_node_append((cc_c99_group_node*)self, node);
}
