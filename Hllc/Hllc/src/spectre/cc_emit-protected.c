/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_emit-protected.h"


#include "cc_os_arraylist.h"
#include "cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"
#include <stdarg.h>
#include <stdio.h>


void cc_emit_write_fv(cc_emit* self, const char *format, va_list arguments)
{
  cc_cstring_buffer_print_v(self->output, format, arguments);
}

void cc_emit_write_f(cc_emit* self, const char* format, ...)
{
  cc_jt jt;
  cc_push_jt(&jt);
  va_list arguments;
  va_start(arguments, format);
  if (!setjmp(jt.env))
  {
    cc_emit_write_fv(self, format, arguments);
    va_end(arguments);
    cc_pop_jt();
  }
  else
  {
    va_end(arguments);
    cc_pop_jt();
    cc_j();
  }
}

static cc_c99_param_node* to_c99_param_node(cc_emit* self, cc_symbol* sym, bool with_name)
{
  if ((sym->flags & CC_SYMBOL_FLAGS_PARAMETER_VARIABLE) == 0)
  { cc_error(CC_EINVAL); }
  cc_c99_node* dst_type = to_c99_type(self, sym->type);
  return cc_c99_node_create_param(sym->name, dst_type, with_name, (sym->flags & CC_SYMBOL_FLAGS_OUT) == CC_SYMBOL_FLAGS_OUT);
}

cc_cstring* cc_emit_compute_name(cc_emit* self, cc_symbol* sym, bool upper_case)
{
  static const uint32_t mask = 
      CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION
    | CC_SYMBOL_FLAGS_SCALAR | CC_SYMBOL_FLAGS_STRUCTURE
    | CC_SYMBOL_FLAGS_MEMBER_VARIABLE
    | CC_SYMBOL_FLAGS_NAMESPACE
    | CC_SYMBOL_FLAGS_METHOD | CC_SYMBOL_FLAGS_CONSTRUCTOR | CC_SYMBOL_FLAGS_DESTRUCTOR;
  if ((sym->flags & mask) == 0)
  {
    fprintf(stderr, "%s:%d: unable to compute the C name of this kind of symbol\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);
  cc_cstring_buffer_append_s(buffer, cc_sym_get_fqn(sym));
  cc_cstring_buffer_replace(buffer, '.', '_');
  if (upper_case)
  {
    cc_cstring_buffer_to_upper(buffer);
  }
  return cc_cstring_buffer_to_string(buffer);
}

cc_c99_node *to_c99_type(cc_emit* self, cc_symbol* sym)
{
  if (sym->flags & CC_SYMBOL_FLAGS_ARRAY)
  {
    return (cc_c99_node*)cc_c99_node_create_pointer_type_declarator(to_c99_type(self, ((cc_syms_array_type *)(sym))->inner_type));
  }
  else
  {
    cc_cstring* temporary = cc_emit_compute_name(self, sym, false);
    if ((sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      cc_c99_node* x;
      x = (cc_c99_node*)cc_c99_node_create_named_type_declarator(temporary);
      x = (cc_c99_node*)cc_c99_node_create_pointer_type_declarator(x);
      return x;
    }
    else
    {
      cc_c99_node* x;
      x = (cc_c99_node*)cc_c99_node_create_named_type_declarator(temporary);
      return x;
    }
  }
}

cc_c99_params_list_node* to_c99_params_list(cc_emit* self, cc_symbol* sym, bool with_self_parameter, bool with_parameter_names, bool multi_line)
{
  if ((sym->flags & CC_SYMBOL_FLAGS_MEMBER_CALLABLE_MASK) == 0)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_INTERNAL, "%s:%d: symbol is not a member callable symbol\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
  cc_arraylist* src_params;
  if (cc_symbol_is_constructor(sym))
  {
    src_params = ((cc_syms_constructor*)sym)->parameters;
  }
  else if (cc_symbol_is_destructor(sym))
  { 
    src_params = ((cc_syms_destructor*)sym)->parameters;
  }
  else if (cc_symbol_is_method(sym))
  { 
    src_params = ((cc_syms_method*)sym)->parameters;
  }
  else
  {
    CC_UNREACHABLE_ERROR();
  }
  cc_c99_params_list_node* dst_params = cc_c99_node_create_params_list(multi_line);

  if ((sym->flags & CC_SYMBOL_FLAGS_STATIC) == 0 && with_self_parameter)
  {
    cc_c99_node* dst_param = to_c99_type(self, sym->enclosing);
    dst_param = (cc_c99_node*)cc_c99_node_create_param(self->names->SELF->string, dst_param, with_parameter_names, false);
    cc_arraylist_append(dst_params->params, (cc_object*)dst_param);
  }

  for (size_t i = 0, n = cc_arraylist_get_size(src_params); i < n; ++i)
  {
    cc_symbol* src_param = (cc_symbol*)cc_arraylist_get_at(src_params, i);
    cc_c99_param_node* dst_param = to_c99_param_node(self, src_param, with_parameter_names);
    cc_arraylist_append(dst_params->params, (cc_object *)dst_param);
  }

  return dst_params;
}

void cc_emit_write_type(cc_emit* self, cc_symbol* sym)
{
  cc_c99_node* x = to_c99_type(self, sym);
  cc_emit_write_node(self, x);
}

void cc_emit_write_indent(cc_emit* self, int indent)
{
  for (int i = 0, n = indent * 2; i < n; ++i)
  {
    cc_emit_write_f(self, " ");
  }
}
