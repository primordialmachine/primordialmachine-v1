#include "c99/cc_c99_param_list_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_params_list_node_visit(cc_c99_params_list_node* self)
{
  CC_VISIT(self->params);
}

static void write_params_list(cc_c99_params_list_node* self, cc_emit* emit)
{ 
  cc_emit_write_indent(emit, emit->indent);

  // Opening delimiter.
  cc_emit_write_f(emit, "(");

  if (self->multi_line)
  {
    cc_emit_write_f(emit, "\n");
    emit->indent += 1;
  }

  for (size_t i = 0, n = cc_arraylist_get_size(self->params); i < n; ++i)
  {
    bool is_last = i == n - 1;
    cc_c99_node* child = (cc_c99_node*)cc_arraylist_get_at(self->params, i);
    if (self->multi_line)
    {
      cc_emit_write_indent(emit, emit->indent);
    }
    cc_emit_write_node(emit, child);
    if (!is_last)
    {
      // If this is not the last parameter, append a comma.
      cc_emit_write_f(emit, ",");
    }
    if (self->multi_line)
    {
      cc_emit_write_f(emit, "\n");
    }
    else if (!is_last)
    {
      cc_emit_write_f(emit, " ");
    }
  }

  if (self->multi_line)
  {
    emit->indent -= 1;
    cc_emit_write_indent(emit, emit->indent);
  }

  // Closing delimiter.
  cc_emit_write_f(emit, ")");
}

CC_DEFINE_CLASS(cc_c99_params_list_node, cc_object, &cc_c99_params_list_node_visit, NULL, NULL, NULL)

cc_c99_params_list_node* cc_c99_node_create_params_list(bool multi_line)
{
  cc_c99_params_list_node* self = (cc_c99_params_list_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_params_list_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_PARAM_LIST;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_params_list;
  self->params = cc_arraylist_create(0);
  self->multi_line = multi_line;
  return self;
}

cc_c99_types_list_node* cc_c99_params_list_to_params_type_list(cc_c99_params_list_node* self, bool multi_line)
{
  cc_c99_types_list_node* target = cc_c99_node_create_types_list(multi_line);
  for (size_t i = 0, n = cc_arraylist_get_size(self->params); i < n; ++i)
  {
    cc_c99_param_node* child = (cc_c99_param_node *)cc_arraylist_get_at(self->params, i);
    cc_arraylist_append(target->types, (cc_object*)child->type);
  }
  return target;
}
