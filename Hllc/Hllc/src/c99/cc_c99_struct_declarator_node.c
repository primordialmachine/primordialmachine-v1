#include "c99/cc_c99_struct_declarator_node.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_struct_declarator_node_visit(cc_c99_struct_declarator_node* self)
{
  CC_VISIT(self->name);
  CC_VISIT(self->body);
}

static void write_struct_declarator(cc_c99_struct_declarator_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "\n");
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "struct %s", self->name->p);
  if (self->body)
  {
    cc_emit_write_f(emit, "\n");
    cc_emit_write_f(emit, "{\n");
    for (size_t i = 0, n = cc_arraylist_get_size(self->body); i < n; ++i)
    {
      cc_c99_node* body_element = (cc_c99_node*)cc_arraylist_get_at(self->body, i);
      cc_emit_write_node(emit, body_element);
    }
    cc_emit_write_indent(emit, emit->indent);
    cc_emit_write_f(emit, "};\n");
  }
  else
  {
    cc_emit_write_f(emit, ";");
  }
}

CC_DEFINE_CLASS(cc_c99_struct_declarator_node, cc_c99_node, &cc_c99_struct_declarator_node_visit, NULL, NULL, NULL)

cc_c99_struct_declarator_node* cc_c99_node_create_struct_declarator(cc_cstring* name)
{
  cc_c99_struct_declarator_node* self = (cc_c99_struct_declarator_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_struct_declarator_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_STRUCT_DECLARATOR;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_struct_declarator;
  self->name = name;
  self->body = NULL;
  return self;
}
