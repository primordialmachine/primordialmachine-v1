/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os_bytebuffer.h"


#include <memory.h>


static void cc_bytebuffer_finalize(cc_bytebuffer* self)
{
  if (self->p)
  {
    cc_dealloc(self->p);
    self->p = NULL;
  }
}

CC_DEFINE_CLASS(cc_bytebuffer, cc_object, NULL, &cc_bytebuffer_finalize, NULL, NULL)

cc_bytebuffer* cc_bytebuffer_create()
{
  cc_type* type = CC_DECORATE(cc_bytebuffer_get_type)();
  cc_bytebuffer* self = (cc_bytebuffer*)cc_object_allocate_2(type);

  self->p = cc_alloc(1024);
  if (!self->p)
  { cc_j(); }
  self->cp = 1024;
  self->sz = 0;

  return self;
}

void cc_bytebuffer_increase_capacity(cc_bytebuffer* self, size_t additional)
{
  if (SIZE_MAX - self->cp < additional)
  {
    cc_error(CC_EOVERFLOW);
  }
  size_t new_cp = self->cp + additional;
  char* new_p = cc_realloc(self->p, new_cp);
  if (!new_p)
  {
    cc_error(CC_ENOMEM);
  }
  self->p = new_p;
  self->cp = new_cp;
}

void cc_bytebuffer_prepend_byte(cc_bytebuffer* self, char byte)
{
  cc_bytebuffer_prepend_bytes(self, &byte, sizeof(char));
}

void cc_bytebuffer_append_byte(cc_bytebuffer* self, char byte)
{
  cc_bytebuffer_append_bytes(self, &byte, sizeof(char));
}

void cc_bytebuffer_prepend_bytes(cc_bytebuffer* self, const char* bytes, size_t number_of_bytes)
{
  if (!self || !bytes)
  {
    cc_error(CC_EINVAL);
  }

  size_t available = self->cp - self->sz;
  if (available < number_of_bytes)
  {
    size_t additional = number_of_bytes - available;
    cc_bytebuffer_increase_capacity(self, additional);
  }

  memmove(self->p + number_of_bytes, self->p, self->sz);
  memcpy(self->p, bytes, number_of_bytes);
  self->sz += number_of_bytes;
}

void cc_bytebuffer_append_bytes(cc_bytebuffer* self, const char* bytes, size_t number_of_bytes)
{
  if (!self || !bytes)
  {
    cc_error(CC_EINVAL);
  }

  size_t available = self->cp - self->sz;
  if (available < number_of_bytes)
  {
    size_t additional = number_of_bytes - available;
    cc_bytebuffer_increase_capacity(self, additional);
  }

  memcpy(self->p + self->sz, bytes, number_of_bytes);
  self->sz += number_of_bytes;
}

void cc_bytebuffer_to_upper(cc_bytebuffer* self)
{
  for (size_t i = 0, n = self->sz; i < n; ++i)
  {
    if ('a' <= self->p[i] && self->p[i] <= 'z')
    {
      self->p[i] = self->p[i] - 32;
    }
  }
}

void cc_bytebuffer_to_lower(cc_bytebuffer* self)
{
  for (size_t i = 0, n = self->sz; i < n; ++i)
  {
    if ('A' <= self->p[i] && self->p[i] <= 'Z')
    {
      self->p[i] = self->p[i] + 32;
    }
  }
}

void cc_bytebuffer_replace(cc_bytebuffer* self, char old, char new)
{
  for (size_t i = 0, n = self->sz; i < n; ++i)
  {
    if (self->p[i] == old)
    {
      self->p[i] = new;
    }
  }
}

void cc_bytebuffer_clear(cc_bytebuffer* self)
{
  self->sz = 0;
}

size_t cc_bytebuffer_get_size(cc_bytebuffer* self)
{
  return self->sz;
}

size_t cc_bytebuffer_get_free_capacity(cc_bytebuffer* self)
{
  return self->cp - self->sz;
}

void cc_bytebuffer_require_free_capacity(cc_bytebuffer* self, size_t required)
{
  size_t available = self->cp - self->sz;
  if (available < required)
  {
    size_t additional = required - available;
    cc_bytebuffer_increase_capacity(self, additional);
  }
}
