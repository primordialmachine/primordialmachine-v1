/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_file_manager.h"


static const char KEY[] = "file-manager";

static void cc_line_map_visit(cc_line_map* self)
{
  CC_VISIT(self->file_path);
}

static void cc_line_map_finalize(cc_line_map* self)
{
  if (self->start_positions)
  {
    cc_dealloc(self->start_positions);
    self->start_positions = NULL;
  }
}

CC_DEFINE_CLASS(cc_line_map, cc_object, &cc_line_map_visit, &cc_line_map_finalize, NULL, NULL)

cc_line_map *
cc_line_map_create
  (
    cc_cstring* file_path,
    cc_bytebuffer* input
  )
{
  cc_type* type = CC_DECORATE(cc_line_map_get_type)();
  cc_line_map* self = (cc_line_map*)cc_object_allocate_2(type);

  self->file_path = file_path;

  // Compute.
  size_t i = 0, n = cc_bytebuffer_get_size(input);
  const char* p = input->p;

  size_t maximum_number_of_start_positions = n, number_of_start_positions = 0;
  size_t* start_positions = cc_alloc_a(sizeof(size_t), maximum_number_of_start_positions);
  if (!start_positions)
  {
    cc_j();
  }
  while (i < n)
  {
    start_positions[number_of_start_positions++] = i;
    do
    {
      // '\n', '\r', '\r\n'.
      if (p[i] == '\n' || p[i] == '\r')
      {
        if (p[i] == '\r' && (i + 1) < n && p[i + 1] == '\n')
        {
          i += 2;
        }
        else
        {
          i += 1;
        }
        break;
      }
    } while (++i < n);
  }

  // Optimize.
  size_t* new_start_positions = cc_realloc_a(start_positions, sizeof(size_t), number_of_start_positions);
  if (!new_start_positions)
  {
    cc_dealloc(start_positions);
    cc_j();
  }
  start_positions = new_start_positions;

  // Store array and array size.
  self->start_positions = start_positions;
  self->number_of_start_positions = number_of_start_positions;

  return self;
}

size_t
cc_line_map_get_start_offset
  (
    cc_line_map* self,
    cc_line_number line_number
  )
{
  size_t line_index = line_number - CC_LINE_NUMBER_LEAST;
  if (line_index >= self->number_of_start_positions)
  {
    cc_error(CC_EINVAL);
  }
  return self->start_positions[line_index];
}

cc_line_number
cc_line_map_get_line
  (
    cc_line_map* self,
    size_t offset
  )
{
  size_t low = 0, high = self->number_of_start_positions - 1;
  while (low <= high)
  {
    size_t median = (low + high) / 2;
    size_t v = self->start_positions[median];
    if (v < offset)
    {
      low = median + 1;
    }
    else if (v > offset)
    {
      high = median - 1;
    }
    // We reach this point if v == offset.
    else
    {
      return ((cc_line_number)median) + CC_LINE_NUMBER_LEAST; // offset is at the beginning of this line.
    }
  }
  return (cc_line_number)low; // offset is on this line.
}

cc_column_number
cc_line_map_get_column
  (
    cc_line_map* self,
    size_t offset
  )
{
  cc_line_number line_number = cc_line_map_get_line(self, offset);
  size_t line_start_offset = self->start_positions[line_number - CC_LINE_NUMBER_LEAST];
  return ((cc_column_number)(offset - line_start_offset)) + CC_COLUMN_NUMBER_LEAST;
}

static void cc_position_visit(cc_position* self)
{
  if (self->line_map)
  {
    cc_visit((cc_object*)self->line_map);
  }
}

CC_DEFINE_CLASS(cc_position, cc_object, &cc_position_visit, NULL, NULL, NULL)

cc_position* cc_position_create(cc_line_map* line_map, cc_file_offset offset)
{
  cc_type* type = CC_DECORATE(cc_position_get_type)();
  cc_position* self = (cc_position*)cc_object_allocate_2(type);

  self->line_map = line_map;
  self->offset = offset;

  return self;
}
