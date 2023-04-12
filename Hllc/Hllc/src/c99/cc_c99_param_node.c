#include "c99/cc_c99_param_node.h"

#include "spectre/cc_c99_node.h"
#include "spectre/c99/type_node.h"

static void cc_c99_param_node_visit(cc_c99_param_node* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->type);
}

static void write_param(cc_c99_param_node* self, cc_emit* emit)
{
  cc_emit_write_node(emit, self->type);
  if (self->with_name)
  {
    cc_emit_write_f(emit, " %s", self->name->p);
  }
}

CC_DEFINE_CLASS(cc_c99_param_node, cc_object, &cc_c99_param_node_visit, NULL, NULL, NULL)

cc_c99_param_node* cc_c99_node_create_param(cc_cstring* name, cc_c99_node* type, bool with_name, bool is_out)
{
  cc_c99_param_node* self = (cc_c99_param_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_param_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_PARAM;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_param;
  self->name = name;
  self->type = type;
  self->with_name = with_name;
  if (is_out)
  {
    self->type = (cc_c99_node *)cc_c99_node_create_pointer_type_declarator(type);
  }
  self->is_out = is_out;
  return self;
}
