#include "c99/cc_c99_enum_element_declarator_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_enum_element_declatator_node_visit(cc_c99_enum_element_declarator_node* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->initializer);
}

static void write_enum_element_declatator(cc_c99_enum_element_declarator_node* self, cc_emit* emit)
{
  emit->indent += 1;
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "%s", self->name->p);
  if (self->initializer)
  {
    cc_emit_write_f(emit, " = ");
    cc_emit_write_node(emit, self->initializer);
  }
  cc_emit_write_f(emit, ",\n");
  emit->indent -= 1;
}

CC_DEFINE_CLASS(cc_c99_enum_element_declarator_node, cc_c99_node, &cc_c99_enum_element_declatator_node_visit, NULL, NULL, NULL)

cc_c99_enum_element_declarator_node* cc_c99_node_create_enum_element_declarator(cc_cstring* name, cc_c99_node* initializer)
{
  cc_c99_enum_element_declarator_node* self = (cc_c99_enum_element_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_enum_element_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_ENUM_ELEMENT_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_enum_element_declatator;
  self->name = name;
  self->initializer = initializer;
  return self;
}
