#include "c99/cc_c99_struct_definition_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_struct_definition_node_visit(cc_c99_struct_definition_node* self)
{
  CC_VISIT(self->declarator);
}

static void write_struct_definition(cc_c99_struct_definition_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "\n");
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "struct %s", self->declarator->name->p);
  cc_emit_write_f(emit, ";");
}

CC_DEFINE_CLASS(cc_c99_struct_definition_node, cc_c99_node, &cc_c99_struct_definition_node_visit, NULL, NULL, NULL)

cc_c99_struct_definition_node* cc_c99_node_create_struct_definition(cc_c99_struct_declarator_node* declarator)
{
  cc_c99_struct_definition_node* self = (cc_c99_struct_definition_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_struct_definition_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_STRUCT_DEFINITION;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_struct_definition;
  self->declarator = declarator;
  return self;
}
