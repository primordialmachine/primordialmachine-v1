/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_LINE_MAP_H_INCLUDED)
#define CC_LINE_MAP_H_INCLUDED


#include "cc_os_lib.h"

/// @brief unsigned integer type for 1-based line numbers.
typedef uint32_t cc_line_number;

#define CC_LINE_NUMBER_LEAST (1)

#define CC_LINE_NUMBER_GREATEST (UINT32_MAX)

/// @brief unsigned integer type for 1-based column numbers.
typedef uint32_t cc_column_number;

#define CC_COLUMN_NUMBER_LEAST (1)

#define CC_COLUMN_NUMBER_GREATEST (UINT32_MAX)

typedef uint64_t cc_file_offset;


/// @brief A line map is a bidirectional mapping between lines/columns and offsets.
/// @extends cc_object
CC_DECLARE_CLASS(cc_line_map, cc_object)

struct cc_line_map
{
  cc_object parent;
  cc_cstring* file_path;
  size_t* start_positions;
  size_t number_of_start_positions;
};

/// @brief Create a line map for the specified input.
/// @param file_path, input
/// @return The line map.
cc_line_map*
cc_line_map_create
  (
    cc_cstring* file_path,
    cc_bytebuffer* input
  );

/// Get the start offset of a line.
/// @param self The line map.
/// @param line_number The line. See cc_line_number.
/// @return The start offset.
size_t
cc_line_map_get_start_offset
  (
    cc_line_map* self,
    cc_line_number line_number
  );

/// @brief Get the line number given an offset.
/// @param self This line map.
/// @param offset The offset.
/// @return The line number.
/// @error CC_EINVAL @a self is null.
uint32_t
cc_line_map_get_line
  (
    cc_line_map* self,
    size_t offset
  );

/// @brief Get the column number given an offset.
/// @param self This line map.
/// @param offset The offset.
/// @return The column number.
/// @error CC_EINVAL @a self is null.
uint32_t
cc_line_map_get_column
  (
    cc_line_map* self,
    size_t offset
  );

/// @brief A position.
/// @extends cc_object
CC_DECLARE_CLASS(cc_position, cc_object)

struct cc_position
{
  cc_object parent;
  cc_line_map* line_map;
  cc_file_offset offset;
};

cc_position* cc_position_create(cc_line_map* line_map, cc_file_offset offset);

#endif // CC_LINE_MAP_H_INCLUDED
