#include "c99/cc_c99_function_declarator_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_function_declarator_node_visit(cc_c99_function_declarator_node* self)
{
  CC_VISIT(self->result_type);
  CC_VISIT(self->name);
  CC_VISIT(self->params);
  CC_VISIT(self->body);
}

static void write_function_declarator(cc_c99_function_declarator_node* self, cc_emit* emit)
{ 
  if (self->is_static)
  {
    cc_emit_write_f(emit, "static");
    cc_emit_write_f(emit, " ");
  }
  cc_emit_write_node(emit, self->result_type);
  cc_emit_write_f(emit, "\n");
  cc_emit_write_f(emit, "%s\n", self->name->p);
  //
  int old_indent = emit->indent;
  emit->indent += 1;
  cc_emit_write_node(emit, (cc_c99_node*)self->params);
  emit->indent = old_indent;
}

CC_DEFINE_CLASS(cc_c99_function_declarator_node, cc_object, &cc_c99_function_declarator_node_visit, NULL, NULL, NULL)

cc_c99_function_declarator_node* cc_c99_node_create_function_declarator(cc_cstring* name, bool is_static, cc_c99_node* result_type, cc_c99_params_list_node* params)
{
  cc_c99_function_declarator_node* self = (cc_c99_function_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_function_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_FUNCTION_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_function_declarator;
  self->result_type = result_type;
  self->name = name;
  self->params = params;
  self->is_static = is_static;
  return self;
}
