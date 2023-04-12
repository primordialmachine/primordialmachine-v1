#include "c99/cc_c99_pp_include_directive.h"

#include "spectre/cc_c99_node.h"

static void cc_c99_pp_include_directive_node_visit(cc_c99_pp_include_directive_node* self)
{
  CC_VISIT(self->include);
}

static void write_pp_include_directive(cc_c99_pp_include_directive_node* self, cc_emit* emit)
{
  cc_emit_write_f(emit, "#include \"%s\"\n", self->include->p);
}

CC_DEFINE_CLASS(cc_c99_pp_include_directive_node, cc_c99_node, &cc_c99_pp_include_directive_node_visit, NULL, NULL, NULL)

cc_c99_pp_include_directive_node* cc_c99_node_create_pp_include_directive(cc_cstring* include)
{
  cc_c99_pp_include_directive_node* self = (cc_c99_pp_include_directive_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_pp_include_directive_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_PP_INCLUDE_DIRECTIVE;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_pp_include_directive;
  self->include = include;
  return self;
}
