/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_emit-protected.h"


#include "spectre/cc_options.h"
#include "spectre/cc_emit_constructors.h"
#include "spectre/cc_emit_destructor.h"
#include "spectre/cc_emit_create_operators.h"
#include "spectre/cc_emit_class_constructor.h"
#include "spectre/cc_emit_member_variable.h"
#include "spectre/cc_emit_expression.h"
#include "spectre/cc_emit_method.h"
#include "spectre/cc_emit_class_struct.h"
#include "spectre/emit/referenced_symbols.h"
#include "spectre/emit/includes.h"
#include "spectre/emit/dispatch.h"
#include "spectre/emit/class.h"
#include "spectre/emit/enumeration.h"
#include "spectre/cc_sym.h"
#include "cc_os_lib.h"
#include <stdio.h>
#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"

#include "spectre/cc_names.h"
#include "spectre/c99/names.h"

#include <stdarg.h>


static const char KEY[] = "emit";

static void cc_emit_visit(cc_emit* self)
{
  CC_VISIT(self->ctx);
  CC_VISIT(self->names);
  CC_VISIT(self->c99_names);
}

static void cc_emit_finalize(cc_emit* self)
{ }

static void emit(cc_emit* self, const char* format, ...)
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

static cc_c99_node* create_runtime_includes()
{
  cc_c99_group_node* root = cc_c99_node_create_group_node();

  // Add "runtime" includes.
  cc_c99_group_node_append(root, (cc_c99_node*)cc_c99_node_create_pp_include_directive(cc_cstring_create("Ring2/_Include.h")));
  cc_c99_group_node_append(root, (cc_c99_node*)cc_c99_node_create_pp_include_directive(cc_cstring_create("Ring2/Library/_Include.h")));
  
  return (cc_c99_node *)root;
}

static cc_emit* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_emit_get_type)();
  cc_emit* self = (cc_emit*)cc_object_allocate_2(type);

  self->names = cc_spectre_names_get_instance(ctx);
  self->c99_names = cc_c99_names_get_instance(ctx);
  self->options = cc_options_get_instance(ctx);
  self->output = cc_cstring_buffer_create();
  self->temporary = cc_cstring_buffer_create();
  self->RUNTIME_INCLUDES = create_runtime_includes();
  self->state_flags = CC_EMIT_STATE_FLAG_BLOCK;
  self->symbols = cc_syms_get_instance(ctx);
  
  return self;
}

DEFINE_COMPONENT(cc_emit, &factory, &cc_emit_visit, &cc_emit_finalize)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Compute the header inlay file pathname of a symbol.
/// @param sym The symbol. 
/// @return The pathname.
static cc_cstring* get_header_inlay(cc_emit* self, cc_symbol* sym)
{
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);

  cc_cstring* fqn = cc_sym_get_fqn(sym);
  cc_cstring_buffer_append_s(buffer, fqn);
  cc_cstring_buffer_replace(buffer, '.', '/');
  cc_cstring_buffer_prepend_p(buffer, "/sources/");
  //cc_cstring_buffer_prepend_p(buffer, "/");
  cc_syms_module* module_sym = (cc_syms_module *)cc_sym_get_enclosing_module(sym);
  cc_cstring_buffer_prepend_s(buffer, module_sym->module_path);
  cc_cstring_buffer_prepend_p(buffer, "./");
  cc_cstring_buffer_append_p(buffer, "-header.i");

  return cc_cstring_buffer_to_string(buffer);
}

/// @brief Compute the footer inlay file pathname of a symbol.
/// @param sym The symbol. 
/// @return The pathname.
static cc_cstring* get_footer_inlay(cc_emit* self, cc_symbol* sym)
{
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);

  cc_cstring* fqn = cc_sym_get_fqn(sym);
  cc_cstring_buffer_append_s(buffer, fqn);
  cc_cstring_buffer_replace(buffer, '.', '/');
  cc_cstring_buffer_prepend_p(buffer, "/sources/");
  //cc_cstring_buffer_prepend_p(buffer, "/");
  cc_syms_module* module_sym = (cc_syms_module *)cc_sym_get_enclosing_module(sym);
  cc_cstring_buffer_prepend_s(buffer, module_sym->module_path);
  cc_cstring_buffer_prepend_p(buffer, "./");
  cc_cstring_buffer_append_p(buffer, "-footer.i");

  return cc_cstring_buffer_to_string(buffer);
}

/// @brief Compute the pathname of the public header of a symbol.
/// @param sym The symbol. 
/// @return The pathname.
static cc_cstring* get_public_header(cc_emit* self, cc_symbol* sym)
{
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);

  cc_cstring* fqn = cc_sym_get_fqn(sym);
  cc_cstring_buffer_append_s(buffer, fqn);
  cc_cstring_buffer_replace(buffer, '.', '/');
  cc_cstring_buffer_prepend_p(buffer, "/sources/");
  //cc_cstring_buffer_prepend_p(buffer, "/");
  cc_syms_module* module_sym = (cc_syms_module *)cc_sym_get_enclosing_module(sym);
  cc_cstring_buffer_prepend_s(buffer, module_sym->module_path);
  cc_cstring_buffer_prepend_p(buffer, "./");
  cc_cstring_buffer_append_p(buffer, ".h");

  return cc_cstring_buffer_to_string(buffer);
}

/// @brief Compute the pathname of the protected header of a symbol.
/// @param sym The symbol. 
/// @return The pathname.
static cc_cstring* get_protected_header(cc_emit* self, cc_symbol* sym)
{
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);

  cc_cstring* fqn = cc_sym_get_fqn(sym);
  cc_cstring_buffer_append_s(buffer, fqn);
  cc_cstring_buffer_replace(buffer, '.', '/');
  cc_cstring_buffer_prepend_p(buffer, "/sources/");
  //cc_cstring_buffer_prepend_p(buffer, "/");
  cc_syms_module* module_sym = (cc_syms_module *)cc_sym_get_enclosing_module(sym);
  cc_cstring_buffer_prepend_s(buffer, module_sym->module_path);
  cc_cstring_buffer_prepend_p(buffer, "./");
  cc_cstring_buffer_append_p(buffer, "-protected.h");

  return cc_cstring_buffer_to_string(buffer);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static bool is_protected(cc_symbol* sym)
{
  return CC_SYMBOL_FLAGS_PROTECTED == (sym->flags & CC_SYMBOL_FLAGS_PROTECTED);
}

static bool is_public(cc_symbol* sym)
{
  return !is_protected(sym);
}

static cc_c99_group_node* 
write_members
  (
    cc_emit *self,
    cc_symbol* sym
  )
{
  if (self->file_context != CC_CLANG_FILE_CONTEXT_PUBLIC && self->file_context != CC_CLANG_FILE_CONTEXT_PROTECTED)
  {
    return NULL;
  }

  cc_c99_group_node* group_node = cc_c99_node_create_group_node();

  for (size_t i = 0, n = cc_arraylist_get_size(sym->enclosed); i < n; ++i)
  {
    cc_symbol* child = (cc_symbol*)cc_arraylist_get_at(sym->enclosed, i);
    if (cc_symbol_is_constructor(child))
    {
      if ((is_protected(child) && self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED) ||
          (is_public(child) && self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC))
      {
        cc_c99_node* xx = cc_emit_constructor(self, child);
        if (xx)
        {
          cc_c99_group_node_append(group_node, xx);
        }
      }
    }
  }

  return group_node;
}

static cc_c99_node *
c99_make_inclusion_guard
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  if (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC)
  {
    cc_cstring* name = cc_emit_compute_name(self, sym, true);
    return (cc_c99_node*)cc_c99_node_create_pp_inclusion_guard(name);
  }
  else if (self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED)
  {
    cc_cstring* name = cc_emit_compute_name(self, sym, true);
    cc_cstring_buffer_clear(self->temporary);
    cc_cstring_buffer_append_s(self->temporary, name);
    cc_cstring_buffer_append_p(self->temporary, "_PROTECTED");
    return (cc_c99_node*)cc_c99_node_create_pp_inclusion_guard(cc_cstring_buffer_to_string(self->temporary));
  }
  else
  {
    return NULL;
  }
}

/// Emit
/// <code>
/// static g_void <qualified_name>_destruct(<qualified_name>* self);
/// static g_void <qualified_name>_class_construct(<qualified_name>_class* self);
/// </code>
static cc_c99_group_node* make_header_decls(cc_emit* self, cc_symbol* sym)
{
  cc_c99_group_node* group_node = cc_c99_node_create_group_node();
  // object destructor
  cc_c99_group_node_append(group_node, (cc_c99_node*)cc_emit_make_object_destructor_declaration(self, sym));
  // class constructor
  cc_c99_group_node_append(group_node, (cc_c99_node*)cc_emit_make_class_constructor_declaration(self, sym));
  return group_node;
}

void write_ty_defn(cc_emit* self, cc_symbol* sym)
{
  cc_c99_node* temporary_node;
  cc_clang_section_context old_section_context;

  cc_cstring* tyn = cc_emit_compute_name(self, sym, false);
  cc_c99_group_node* old_root_node = cc_c99_node_create_group_node();

  {
    cc_cstring_buffer* buffer = self->temporary;
    cc_cstring_buffer_clear(buffer);
    cc_cstring* s = cc_sym_get_fqn(sym);
    cc_cstring_buffer_append_s(buffer, s);
    cc_cstring_buffer_replace(buffer, '.', '/');
    cc_cstring_buffer_prepend_s(buffer, cc_cstring_create("/// @file "));
    cc_cstring_buffer_append_s(buffer, cc_cstring_create(".h"));
    s = cc_cstring_buffer_to_string(buffer);
    temporary_node = (cc_c99_node*)cc_c99_node_create_text_line(s);
    cc_c99_group_node_append(old_root_node, temporary_node);
  }
  temporary_node = (cc_c99_node *)cc_c99_node_create_text_line(cc_cstring_create("/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved."));
  cc_c99_group_node_append(old_root_node, temporary_node);
  temporary_node = (cc_c99_node *)cc_c99_node_create_text_line(cc_cstring_create("/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)"));
  cc_c99_group_node_append(old_root_node, temporary_node);

  // "inclusion guard" node.
  cc_c99_node* inclusion_guard_node = c99_make_inclusion_guard(self, sym);
  if (inclusion_guard_node)
  { cc_c99_group_node_append(old_root_node, inclusion_guard_node); }
  
  // "extern C" node for all files.
  cc_c99_node* extern_c_node = (cc_c99_node *)cc_c99_node_create_pp_extern_c_node();
  cc_c99_group_node_append(inclusion_guard_node ? (cc_c99_group_node*)inclusion_guard_node : (cc_c99_group_node *)old_root_node, extern_c_node);

  cc_c99_group_node* root_node = cc_c99_node_create_group_node();
  cc_c99_group_node_append((cc_c99_group_node*)extern_c_node, (cc_c99_node *)root_node);

  // self include for protected header and header inlay files.
  if (self->file_context == CC_CLANG_FILE_CONTEXT_HEADER_INLAY)
  {
    temporary_node = (cc_c99_node *)cc_emit_get_additional_includes_for(self, CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_HEADER_INLAY, sym);
    if (temporary_node)
    { cc_c99_group_node_append(root_node, temporary_node); }
  }
  else if (self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED)
  {
    temporary_node = (cc_c99_node *)cc_emit_get_additional_includes_for(self, CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_PROTECTED_HEADER, sym);
    if (temporary_node)
    { cc_c99_group_node_append(root_node, temporary_node); }
  }

  if (self->file_context == CC_CLANG_FILE_CONTEXT_HEADER_INLAY)
  {
    if ((sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      if (!sym->parent)
      {
        cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: class has no parent type\n", __FILE__, __LINE__);
        cc_error(CC_EINVAL);
      }

      cc_c99_group_node* header_decls = make_header_decls(self, sym);
      cc_c99_group_node_append(root_node, (cc_c99_node*)header_decls);

      cc_c99_text_line_node* text_line;

      text_line = cc_c99_node_create_text_line(self->c99_names->EMPTY->string);
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);

      cc_cstring* ptyn = cc_emit_compute_name(self, sym->parent, false);
      cc_cstring_buffer_clear(self->temporary);
      cc_cstring_buffer_append_p(self->temporary, "MACHINE_DEFINE_CLASSTYPE(");
      cc_cstring_buffer_append_s(self->temporary, tyn);
      cc_cstring_buffer_append_p(self->temporary, ", ");
      cc_cstring_buffer_append_s(self->temporary, ptyn);
      cc_cstring_buffer_append_p(self->temporary, ")");

      text_line = cc_c99_node_create_text_line(cc_cstring_buffer_to_string(self->temporary));
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);

      temporary_node = (cc_c99_node*)cc_emit_make_object_destructor_definition(self, sym);
      if (temporary_node)
      {
        cc_c99_group_node_append(root_node, temporary_node);
      }
    }
    
    if (cc_symbol_is_enumeration(sym))
    {
      cc_c99_text_line_node* text_line;

      text_line = cc_c99_node_create_text_line(self->c99_names->EMPTY->string);
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);

      cc_cstring_buffer_clear(self->temporary);
      cc_cstring_buffer_append_p(self->temporary, "MACHINE_DEFINE_ENUMERATIONTYPE(");
      cc_cstring_buffer_append_s(self->temporary, tyn);
      cc_cstring_buffer_append_p(self->temporary, ")");
      
      text_line = cc_c99_node_create_text_line(cc_cstring_buffer_to_string(self->temporary));
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);
    }
  }
  
  if (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC)
  {
    temporary_node = (cc_c99_node *)cc_emit_get_additional_includes_for(self, CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_PUBLIC_HEADER, sym);
    if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);

    if ((sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      cc_c99_text_line_node* text_line;

      text_line = cc_c99_node_create_text_line(self->c99_names->EMPTY->string);
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);

      cc_cstring_buffer_clear(self->temporary);
      cc_cstring_buffer_append_p(self->temporary, "MACHINE_DECLARE_CLASSTYPE(");
      cc_cstring_buffer_append_s(self->temporary, tyn);
      cc_cstring_buffer_append_p(self->temporary, ")");
      
      text_line = cc_c99_node_create_text_line(cc_cstring_buffer_to_string(self->temporary));
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);
    }
    else if (cc_symbol_is_enumeration(sym))
    {
      cc_c99_text_line_node* text_line;

      text_line = cc_c99_node_create_text_line(self->c99_names->EMPTY->string);
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);

      cc_cstring_buffer_clear(self->temporary);
      cc_cstring_buffer_append_p(self->temporary, "MACHINE_DECLARE_ENUMERATIONTYPE(");
      cc_cstring_buffer_append_s(self->temporary, tyn);
      cc_cstring_buffer_append_p(self->temporary, ")");
      
      text_line = cc_c99_node_create_text_line(cc_cstring_buffer_to_string(self->temporary));
      cc_c99_group_node_append(root_node, (cc_c99_node*)text_line);
    }
    else
    {
      cc_set_status(CC_EINVAL);
    }

    if ((self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC) && cc_symbol_is_enumeration(sym))
    {
      temporary_node = (cc_c99_node *)cc_emit_make_enumeration_type_enum(self, sym);
      if (temporary_node) { cc_c99_group_node_append(root_node, temporary_node); }
    }

    if ((self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC) && cc_symbol_is_class(sym))
    {
      temporary_node = (cc_c99_node *)cc_emit_make_class_type_struct(self, sym);
      if (temporary_node) { cc_c99_group_node_append(root_node, temporary_node); }
    }

    if ((self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC) && (sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      temporary_node = (cc_c99_node*)cc_emit_make_class_struct(self, sym);
      if (temporary_node) { cc_c99_group_node_append(root_node, temporary_node); }
    }
  }

  if (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC || self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED)
  {
    // This writes the object constructors.
    old_section_context = self->section_context;
    self->section_context = CC_CLANG_SECTION_CONTEXT_FUNCTION_DECLS;
    temporary_node = (cc_c99_node*)write_members(self, sym);
    cc_c99_group_node_append(root_node, temporary_node);
    self->section_context = old_section_context;
  }

  if (self->file_context == CC_CLANG_FILE_CONTEXT_HEADER_INLAY && (sym->flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION)) != 0)
  {
    temporary_node = (cc_c99_node*)cc_emit_get_dispatch_declarations(self, CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_HEADER_INLAY, sym);
    if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);
  }
  if (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC && (sym->flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION)) != 0)
  {
    temporary_node = (cc_c99_node*)cc_emit_get_dispatch_declarations(self, CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PUBLIC_HEADER, sym);
    if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);
  }
  if (self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED && (sym->flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION)) != 0)
  {
    temporary_node = (cc_c99_node*)cc_emit_get_dispatch_declarations(self, CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PROTECTED_HEADER, sym);
    if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);
  }
  if (self->file_context == CC_CLANG_FILE_CONTEXT_FOOTER_INLAY)
  {
    temporary_node = (cc_c99_node*)cc_emit_get_dispatch_declarations(self, CC_EMIT_DISPATCH_GENERATION_STRATEGY_DEFINITIONS_FOOTER_INLAY, sym);
    if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);
  }

  temporary_node = (cc_c99_node *)cc_emit_make_class_constructor_definition(self, sym);
  if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);
  temporary_node = (cc_c99_node *)cc_emit_make_create_operators(self, sym);
  if (temporary_node) cc_c99_group_node_append(root_node, temporary_node);

  cc_emit_write_node(self, (cc_c99_node*)old_root_node);
}

static void write_ty_protected(cc_emit* self, cc_symbol* sym)
{
  // Clear the buffer.
  cc_cstring_buffer_clear(self->output);

  self->file_context = CC_CLANG_FILE_CONTEXT_PROTECTED;
  if ((sym->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  {
    return;
  }
  cc_cstring* pathname = get_protected_header(self, sym);
  if (cc_options_get_mode(self->options) == CC_OPTIONS_MODE_CLEAN)
  {
    remove(pathname->p);
  }
  else
  {
    write_ty_defn(self, sym);
    cc_set_file_contents_from_cstring_buffer(pathname, self->output);
  }
}

static void write_ty_header_inlay(cc_emit* self, cc_symbol* sym)
{
  // Clear the buffer.
  cc_cstring_buffer_clear(self->output);

  self->file_context = CC_CLANG_FILE_CONTEXT_HEADER_INLAY;
  if ((sym->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  {
    return;
  }
  cc_cstring* pathname = get_header_inlay(self, sym);
  if (cc_options_get_mode(self->options) == CC_OPTIONS_MODE_CLEAN)
  {
    remove(pathname->p);
  }
  else
  {
    write_ty_defn(self, sym);
    cc_set_file_contents_from_cstring_buffer(pathname, self->output);
  }
}

static void write_ty_footer_inlay(cc_emit* self, cc_symbol* sym)
{
  // Clear the buffer.
  cc_cstring_buffer_clear(self->output);

  self->file_context = CC_CLANG_FILE_CONTEXT_FOOTER_INLAY;
  if ((sym->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  {
    return;
  }
  cc_cstring* pathname = get_footer_inlay(self, sym);
  if (cc_options_get_mode(self->options) == CC_OPTIONS_MODE_CLEAN)
  {
    remove(pathname->p);
  }
  else
  {
    write_ty_defn(self, sym);
    cc_set_file_contents_from_cstring_buffer(pathname, self->output);
  }
}

static void write_ty_public(cc_emit* self, cc_symbol* sym)
{
  // Clear the buffer.
  cc_cstring_buffer_clear(self->output);

  self->file_context = CC_CLANG_FILE_CONTEXT_PUBLIC;
  if ((sym->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  {
    return;
  }
  cc_cstring* pathname = get_public_header(self, sym);
  if (cc_options_get_mode(self->options) == CC_OPTIONS_MODE_CLEAN)
  {
    remove(pathname->p);
  }
  else
  {
    write_ty_defn(self, sym);
    cc_set_file_contents_from_cstring_buffer(pathname, self->output);
  }
}

static void write_ty(cc_emit* self, cc_symbol* sym)
{
  write_ty_public(self, sym);
  if (!cc_symbol_is_enumeration(sym)) {
    write_ty_protected(self, sym);
  }
  //write_ty_header_inlay(self, sym);
  //write_ty_footer_inlay(self, sym);
}

void cc_emit_run(cc_emit* self)
{
  cc_jt jt;
  cc_push_jt(&jt);
  if (!setjmp(jt.env))
  {
    for (cc_symbol* sym = cc_sym_first(self->ctx); NULL != sym; sym = cc_sym_next(sym))
    {
      if ((sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS || cc_symbol_is_enumeration(sym))
      {
        write_ty(self, sym);
      }
    }
    cc_pop_jt();
  }
  else
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: internal error\n");
    cc_pop_jt();
    cc_j();
  }
}
