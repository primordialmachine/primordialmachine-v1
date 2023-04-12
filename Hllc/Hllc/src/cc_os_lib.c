/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os_lib.h"


#include <stdarg.h>

#include <malloc.h>
#include <memory.h>

#include <stdio.h>

#include <string.h>
#include "spectre/cc_ascii.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void cc_get_file_contents_ex(cc_cstring* file_path, cc_bytebuffer* buffer)
{
#define BUFFER_CAPACITY (1024)

  if (!file_path)
  {
    cc_error(CC_EINVAL);
  }
  FILE* fd = fopen(file_path->p, "rb");
  if (!fd)
  {
    fprintf(stderr, "%s:%d: unable to open file %s for reading\n", __FILE__, __LINE__, file_path->p);
    cc_error(CC_ENOENT);
  }
  cc_jt jt;
  cc_push_jt(&jt);
  if (!setjmp(jt.env))
  {
    while (true)
    {
      char p[BUFFER_CAPACITY];
      size_t n = fread(p, 1, BUFFER_CAPACITY, fd);
      if (n != BUFFER_CAPACITY && n != 0)
      {
        if (ferror(fd))
        {
          fprintf(stderr, "%s:%d: error while reading file %s\n", __FILE__, __LINE__, file_path->p);
          cc_error(CC_ENOENT);
        }
        else if (feof(fd))
        {
          cc_bytebuffer_append_bytes(buffer, p, n);
          break;
        }
      }
      else if (n == 0)
      {
        if (ferror(fd))
        {
          fprintf(stderr, "%s:%d: error while reading file %s\n", __FILE__, __LINE__, file_path->p);
          cc_error(CC_ENOENT);
        }
        else if (feof(fd))
        {
          break;
        }
        else
        {
          // TODO: Short-read. Keep track of short reads and abort if consecutive short reads occur a certain number of times.
          fprintf(stderr, "%s:%d: short read file reading file %s\n", __FILE__, __LINE__, file_path->p);
        }
      }
      else
      {
        cc_bytebuffer_append_bytes(buffer, p, n);
      }
    }
    if (fd)
    {
      fclose(fd);
      fd = NULL;
    }
    cc_pop_jt();
  }
  else
  {
    if (fd)
    {
      fclose(fd);
      fd = NULL;
    }
    cc_pop_jt();
    cc_j();
  }

#undef BUFFER_CAPACITY
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_cstring_buffer_visit(cc_cstring_buffer* self)
{
  CC_VISIT(self->byte_buffer);
}

CC_DEFINE_CLASS(cc_cstring_buffer, cc_object, &cc_cstring_buffer_visit, NULL, NULL, NULL)

cc_cstring_buffer* cc_cstring_buffer_create()
{
  cc_type* type = CC_DECORATE(cc_cstring_buffer_get_type)();
  cc_cstring_buffer* self = (cc_cstring_buffer*)cc_object_allocate_2(type);

  self->byte_buffer = cc_bytebuffer_create();
  cc_bytebuffer_append_byte(self->byte_buffer, '\0');

  return self;
}

cc_cstring_buffer* cc_cstring_buffer_create_p(const char* p)
{
  cc_type* type = CC_DECORATE(cc_cstring_buffer_get_type)();
  cc_cstring_buffer* self = (cc_cstring_buffer*)cc_object_allocate_2(type);

  self->byte_buffer = cc_bytebuffer_create();
  cc_bytebuffer_append_bytes(self->byte_buffer, p, strlen(p) + 1);

  return self;
}

cc_cstring_buffer* cc_cstring_buffer_create_s(cc_cstring* s)
{
  cc_type* type = CC_DECORATE(cc_cstring_buffer_get_type)();
  cc_cstring_buffer* self = (cc_cstring_buffer*)cc_object_allocate_2(type);

  self->byte_buffer = cc_bytebuffer_create();
  cc_bytebuffer_append_bytes(self->byte_buffer, s->p, strlen(s->p) + 1);

  return self;
}

cc_cstring* cc_cstring_buffer_to_string(cc_cstring_buffer* self)
{
  return cc_cstring_create(self->byte_buffer->p);
}

void cc_cstring_buffer_to_lower(cc_cstring_buffer* self)
{
  cc_ascii_to_lower(self->byte_buffer->p, self->byte_buffer->sz - 1);
}

void cc_cstring_buffer_to_upper(cc_cstring_buffer* self)
{
  cc_ascii_to_upper(self->byte_buffer->p, self->byte_buffer->sz - 1);
}

void cc_cstring_buffer_replace(cc_cstring_buffer* self, char old, char new)
{
  cc_ascii_replace(self->byte_buffer->p, self->byte_buffer->sz - 1, old, new);
}

void cc_cstring_buffer_clear(cc_cstring_buffer* self)
{
  cc_bytebuffer_clear(self->byte_buffer);
  cc_bytebuffer_append_byte(self->byte_buffer, '\0');
}

size_t cc_cstring_buffer_get_size(cc_cstring_buffer* self)
{
  return cc_bytebuffer_get_size(self->byte_buffer) - 1;
}

void cc_cstring_buffer_prepend_p(cc_cstring_buffer* self, const char* string)
{
  cc_bytebuffer_prepend_bytes(self->byte_buffer, string, strlen(string));
}

void cc_cstring_buffer_prepend_s(cc_cstring_buffer* self, cc_cstring* string)
{
  cc_bytebuffer_prepend_bytes(self->byte_buffer, string->p, strlen(string->p));
}

void cc_cstring_buffer_append_p(cc_cstring_buffer* self, const char* string)
{
  self->byte_buffer->sz--; // Remove existing trailing zero terminator.
  cc_bytebuffer_append_bytes(self->byte_buffer, string, strlen(string) + 1);
}

void cc_cstring_buffer_append_s(cc_cstring_buffer* self, cc_cstring* string)
{
  self->byte_buffer->sz--;
  cc_bytebuffer_append_bytes(self->byte_buffer, string->p, strlen(string->p) + 1);
}

void cc_cstring_buffer_print_v(cc_cstring_buffer* self, const char* format, va_list arguments)
{
  va_list arguments2;
  va_copy(arguments2, arguments);
  cc_jt jt;
  cc_push_jt(&jt);
  if (!setjmp(jt.env))
  {
    int r1, r2;
    r1 = vsnprintf(NULL, 0, format, arguments);
    if (r1 < 0)
    {
      cc_error(CC_EINVAL);
    }
    // vsnprintf will write r1 + 1 Bytes to the Byte buffer.
    // So we require a free capacity of r + 1.
    // However, the last Byte in the Byte buffer is the zero terminator which we are going to overwrite.
    // So we only require a free capacity of r1.
    cc_bytebuffer_require_free_capacity(self->byte_buffer, (size_t)r1);
    // -1 to overwrite the old zero terminator.
    char* dst = self->byte_buffer->p + (self->byte_buffer->sz - 1);
    size_t dst_sz = ((size_t)r1) + 1;
    r2 = vsnprintf(dst, dst_sz, format, arguments2);
    if (r2 < 0 || r1 != r2)
    {
      cc_error(CC_EINVAL);
    }
    self->byte_buffer->sz += (size_t)r2;

    cc_pop_jt();
    va_end(arguments2);
  }
  else
  {
    cc_pop_jt();
    va_end(arguments2);
    cc_j();
  }
}

void
cc_set_file_contents_from_byte_buffer
  (
    cc_cstring* file_path,
    cc_bytebuffer* source,
    size_t start_index,
    size_t end_index
  )
{
  if (start_index < 0 || start_index >= source->sz)
  {
    fprintf(stderr, "%s:%d: error writing file '%s': start index out of bounds\n", __FILE__, __LINE__, file_path->p);
    cc_error(CC_EINVAL);
  }
  if (end_index < 0 || end_index >= source->sz)
  {
    fprintf(stderr, "%s:%d: error writing file '%s': end index out of bounds\n", __FILE__, __LINE__, file_path->p);
    cc_error(CC_EINVAL);
  }
  if (start_index > end_index)
  {
    fprintf(stderr, "%s:%d: error writing file '%s': start index greater than end index\n", __FILE__, __LINE__, file_path->p);
    cc_error(CC_EINVAL);
  }

  FILE* fd = fopen(file_path->p, "w");
  if (!fd)
  {
    fprintf(stderr, "%s:%d: error writing file '%s': unable to open file\n", __FILE__, __LINE__, file_path->p);
    cc_error(CC_EINVAL);
  }

  size_t required = end_index - start_index;
  size_t actual = fwrite(source->p, 1, required, fd);
  if (actual != required)
  {
    fclose(fd);
    fd = NULL;
    fprintf(stderr, "%s:%d: error writing file '%s' unable to write %zu Bytes\n", __FILE__, __LINE__, file_path->p, required);
    cc_error(CC_EINVAL);
  }

  fclose(fd);
  fd = NULL;
}

void
cc_set_file_contents_from_cstring_buffer
  (
    cc_cstring* file_path,
    cc_cstring_buffer* source
  )
{
  size_t start_index = 0;
  size_t end_index = source->byte_buffer->sz - 1;
  cc_set_file_contents_from_byte_buffer(file_path, source->byte_buffer, start_index, end_index);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void cc_print_fv(cc_print_flags flags, const char* format, va_list arguments)
{
  if (flags == 0)
  {
    vfprintf(stdout, format, arguments);
  }
  if (flags & CC_PRINT_FLAG_ERROR)
  {
    vfprintf(stderr, format, arguments);
  }
  else
  {
    vfprintf(stdout, format, arguments);
  }
}

void cc_print_f(cc_print_flags flags, const char* format, ...)
{
  va_list arguments;
  va_start(arguments, format);
  cc_print_fv(flags, format, arguments);
  va_end(arguments);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_tool_visit(cc_tool *self)
{
  CC_VISIT(self->name);
}

CC_DEFINE_CLASS(cc_tool, cc_object, &cc_tool_visit, NULL, NULL, NULL)

cc_tool *cc_tool_create(cc_cstring* name, void (*run)(cc_tool *self, cc_arraylist* args))
{
  CC_ASSERT_NOT_NULL(name);
  CC_ASSERT_NOT_NULL(run);

  cc_type* type = CC_DECORATE(cc_tool_get_type)();
  cc_tool* self = (cc_tool *)cc_object_allocate_2(type);

  self->name = name;
  self->run = run;

  return self;
}
