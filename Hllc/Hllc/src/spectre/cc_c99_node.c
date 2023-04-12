#include "spectre/cc_c99_node.h"

#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"

static void cc_c99_node_visit(cc_c99_node* self)
{ }

CC_DEFINE_CLASS(cc_c99_node, cc_object, &cc_c99_node_visit, NULL, NULL, NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_c99_types_list_node_visit(cc_c99_types_list_node* self)
{
  CC_VISIT(self->types);
}

static void write_types_list(cc_c99_types_list_node* self, cc_emit* emit)
{
  bool multi_line = self->multi_line;
  bool block = (emit->state_flags & CC_EMIT_STATE_FLAG_BLOCK) == CC_EMIT_STATE_FLAG_BLOCK;
  if (block)
  {
    cc_emit_write_indent(emit, emit->indent);
  }
  // Opening delimiter.
  cc_emit_write_f(emit, "(");

  if (block && multi_line)
  {
    cc_emit_write_f(emit, "\n");
    emit->indent += 1;
  }

  for (size_t i = 0, n = cc_arraylist_get_size(self->types); i < n; ++i)
  {
    bool is_last = i == n - 1;
    cc_c99_node* child = (cc_c99_node*)cc_arraylist_get_at(self->types, i);
    if (block && multi_line)
    {
      cc_emit_write_indent(emit, emit->indent);
    }
    cc_emit_write_node(emit, child);
    if (!is_last)
    {
      // If this is not the last parameter, append a comma.
      cc_emit_write_f(emit, ",");
    }
    if (block && multi_line)
    {
      cc_emit_write_f(emit, "\n");
    }
    else if (!is_last)
    {
      cc_emit_write_f(emit, " ");
    }
  }

  if (block & multi_line)
  {
    emit->indent -= 1;
    cc_emit_write_indent(emit, emit->indent);
  }

  // Closing delimiter.
  cc_emit_write_f(emit, ")");
}

CC_DEFINE_CLASS(cc_c99_types_list_node, cc_object, &cc_c99_types_list_node_visit, NULL, NULL, NULL)

cc_c99_types_list_node* cc_c99_node_create_types_list(bool multi_line)
{
  cc_c99_types_list_node* self = (cc_c99_types_list_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_types_list_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_TYPE_LIST;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_types_list;
  self->types = cc_arraylist_create(0);
  self->multi_line = multi_line;
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_c99_text_line_node_visit(cc_c99_text_line_node* self)
{
  CC_VISIT(self->text);
}

static void write_text_line(cc_c99_text_line_node* self, cc_emit* emit)
{
  cc_emit_write_indent(emit, emit->indent);
  cc_emit_write_f(emit, "%s", self->text->p);
  cc_emit_write_f(emit, "\n");
}

CC_DEFINE_CLASS(cc_c99_text_line_node, cc_c99_node, &cc_c99_text_line_node_visit, NULL, NULL, NULL)

cc_c99_text_line_node* cc_c99_node_create_text_line(cc_cstring* text)
{
  cc_c99_text_line_node* self = (cc_c99_text_line_node*)cc_object_allocate_2(CC_DECORATE(cc_c99_text_line_node_get_type)());
  ((cc_c99_node*)self)->kind = CC_C99_NODE_KIND_TEXT_LINE;
  ((cc_c99_node*)self)->write = (void (*)(cc_c99_node*, cc_emit*)) & write_text_line;
  self->text = text;
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void cc_emit_write_node(cc_emit* self, cc_c99_node* node)
{
  (*node->write)(node, self);
}
