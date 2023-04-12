#include "c99/cc_c99_function_declaration_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_function_declaration_node_visit(cc_c99_function_declaration_node* self)
{
  CC_VISIT(self->declarator);
}

static void write_function_declaration(cc_c99_function_declaration_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "\n");
  
  cc_emit_write_indent(emit, emit->indent);
  if (self->declarator->is_static)
  {
    cc_emit_write_f(emit, "static ");
  }
  
  cc_emit_write_node(emit, self->declarator->result_type);
  cc_emit_write_f(emit, "\n");
  
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "%s\n", self->declarator->name->p);
  
  emit->indent += 1;
  cc_emit_write_node(emit, (cc_c99_node*)self->declarator->params);
  emit->indent -= 1;

  cc_emit_write_f(emit, ";");
  cc_emit_write_f(emit, "\n");
}

CC_DEFINE_CLASS(cc_c99_function_declaration_node, cc_object, &cc_c99_function_declaration_node_visit, NULL, NULL, NULL)

cc_c99_function_declaration_node* cc_c99_node_create_function_declaration(cc_c99_function_declarator_node* declarator)
{
  cc_c99_function_declaration_node* self = (cc_c99_function_declaration_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_function_declaration_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_FUNCTION_DECLARATION;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_function_declaration;
  self->declarator = declarator;
  return self;
}
