#if !defined(CC_EMIT_PROTECTED_H_INCLUDED)
#define CC_EMIT_PROTECTED_H_INCLUDED


#include "cc_emit.h"
#include "cc_sym.h"
typedef struct cc_c99_params_list_node cc_c99_params_list_node;
typedef struct cc_c99_function_declarator_node cc_c99_function_declarator_node;


/// @brief Write a formatted string.
/// @param self The emit stage.
/// @param format The format string and the format arguments.
void cc_emit_write_fv(cc_emit* self, const char *format, va_list arguments);

/// @brief Write a formatted string.
/// @param self The emit stage.
/// @param format, ... The format string and the format arguments.
void cc_emit_write_f(cc_emit* self, const char* format, ...);

/// Compute the C name of a symbol.
/// @param sym A
/// - class/enumeration,
/// - scalar/structure,
/// - member variable,
/// - namespace, or
/// - constructor/destruct/method
/// symbol.
cc_cstring* cc_emit_compute_name(cc_emit* self, cc_symbol* sym, bool upper_case);

/// Write a type
/// <code>
/// write_type(T.inner) *
/// </code>
/// if T is an array type with an inner type T.inner.
/// <code>
/// Write a type
/// <code>
/// write(compute_name(T)) *
/// </code>
/// if T a class type.
/// Write a type
/// <code>
/// write(compute_fqn(T))
/// </code>
/// if T not an array type nor a class type.
void cc_emit_write_type(cc_emit* self, cc_symbol* sym);

// @a sym must be a type symbol.
cc_c99_node* to_c99_type(cc_emit* self, cc_symbol* sym);

/// @a sym must be a constructor, destructor, or method symbol.
/// @param include_self
/// The C99 parameter lists of non-static methods, constructors, and destructors have the self parameter synthesized if this is @a true.
/// Otherwise that parameter is not synthesized.
/// Meaningless for static methods.
cc_c99_params_list_node* to_c99_params_list(cc_emit* self, cc_symbol* sym, bool with_self_parameter, bool with_parameter_names, bool multi_line);

/// Write indent * 2 whitespaces.
void cc_emit_write_indent(cc_emit* self, int indent);

typedef struct cc_emit_parameter_list_format
{
  /// Emit the name of each parameter if @a true.
  /// Otherwise do not.
  bool emit_parameter_name;

  /// Place each parameter in a new line if @a true.
  /// Otherwise do not.
  bool multi_line_parameter_list;

  /// The indent.
  int indent;

} cc_emit_parameter_list_format;



#endif // CC_EMIT_PROTECTED_H_INCLUDED
