/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

// Token types & scanner.

#if !defined(CC_SCANNER_H_INCLUDED)
#define CC_SCANNER_H_INCLUDED

#include "cc_file_manager.h"
#include "cc_context.h"
#include "cc_names.h"

typedef enum cc_token_kind
{

#define DEFINE(name, string) \
  CC_TKT_##name,

#include "spectre/cc_token_kind.i"

#undef DEFINE

} cc_token_kind;

cc_cstring* cc_token_kind_to_string(cc_token_kind self);

BEGIN_DECLARE_COMPONENT(cc_scanner)

  /// @brief The file path of the input.
  /// @a input, @a start, @a end, and @a current are all invalid if this is null.
  cc_cstring* file_path;

  /// @brief  The line map of the input.
  /// @a input, @a start, @a end, and @a current are all invalid if this is null.
  cc_line_map* line_map;

  cc_spectre_names* names;

  cc_bytebuffer* input;
  char* start, * current, * end;

  struct
  {
    /// @brief The kind of the current token.
    int kind;

    struct
    {

      /// @brief The start offset of the current token.
      size_t start;

      /// @brief The end offset of the current token.
      size_t end;

    } range;

    /// @brief The text of the current token.
    struct
    {
      char elems[1024];
      size_t nelems;
    } text;

  } token;

END_DECLARE_COMPONENT(cc_scanner)

void cc_scanner_set_input(cc_scanner* scanner, cc_cstring* file_path);

void cc_scanner_step(cc_scanner* scanner);

/// @brief Get the line map of the input.
/// @param self This scanner.
/// @return The line map.
cc_line_map* cc_scanner_get_line_map(cc_scanner* self);

/// @brief Get the start offset of the current token.
/// @param self This scanner.
/// @return The start offset.
cc_file_offset cc_scanner_get_start_offset(cc_scanner* self);

/// @brief Get the end offset of the current token.
/// @param self This scanner.
/// @return The end offset.
cc_file_offset cc_scanner_get_end_offset(cc_scanner* self);

/// @brief Get the file path of the current token.
/// @param self This scanner.
/// @return The file path of the curren token.
cc_cstring* cc_scanner_get_file_path(cc_scanner* self);

/// @brief Get the type of the current token.
/// @param self This scanner.
/// @return The type of the current token.
int cc_scanner_get_kind(cc_scanner* self);

/// @brief Get the text of the current token.
/// @param self This scanner.
/// @return The text of the current token.
cc_name* cc_scanner_get_text(cc_scanner* self);

#endif // CC_SCANNER_H_INCLUDED
