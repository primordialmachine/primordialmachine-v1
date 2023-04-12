#include "c99/cc_c99_pp_inclusion_guard.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_pp_inclusion_guard_node_visit(cc_c99_pp_inclusion_guard_node *self)
{
  CC_VISIT(self->name);
}

static void write_pp_inclusion_guard(cc_c99_pp_inclusion_guard_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "#if !defined(%s_H_INCLUDED)\n", self->name->p);
  cc_emit_write_f(emit, "#define %s_H_INCLUDED\n", self->name->p);

  for (size_t i = cc_arraylist_get_size(((cc_c99_group_node*)self)->children); i > 0; --i)
  {
    cc_c99_node* child = (cc_c99_node *)cc_arraylist_get_at(((cc_c99_group_node*)self)->children, i - 1);
    cc_emit_write_node(emit, child);
  }

  cc_emit_write_f(emit, "\n");
  cc_emit_write_f(emit, "#endif // %s_H_INCLUDED\n", self->name->p);
}

CC_DEFINE_CLASS(cc_c99_pp_inclusion_guard_node, cc_c99_group_node, &cc_c99_pp_inclusion_guard_node_visit, NULL, NULL, NULL)

cc_c99_pp_inclusion_guard_node* cc_c99_node_create_pp_inclusion_guard(cc_cstring *name)
{
  cc_c99_pp_inclusion_guard_node* self = (cc_c99_pp_inclusion_guard_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_pp_inclusion_guard_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_PP_INCLUSION_GUARD;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node *, cc_emit *))&write_pp_inclusion_guard;
  ((cc_c99_group_node*)self)->children = cc_arraylist_create(0);
  self->name = name;
  return self;
}

void cc_c99_pp_inclusion_guard_node_append(cc_c99_pp_inclusion_guard_node* self, cc_c99_node* node)
{
  cc_c99_group_node_append((cc_c99_group_node*)self, node);
}
