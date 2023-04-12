/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os_arraylist.h"


#include <memory.h>
#include "cc_os_lib.h"


static void grow(cc_object*** elements, size_t *size, size_t *capacity)
{
  static const size_t MAX_CAPACITY = SIZE_MAX / sizeof(cc_object*);
  size_t old_capacity = *capacity;
  size_t new_capacity;
  if (MAX_CAPACITY / 2 < old_capacity)
  {
    new_capacity = MAX_CAPACITY;
  }
  else
  {
    new_capacity = old_capacity > 0 ? old_capacity * 2 : 8;
  }
  if (new_capacity == old_capacity)
  {
    cc_error(CC_ENOMEM);
  }
  cc_object** new_elements = cc_realloc_a(*elements, sizeof(cc_object *), new_capacity);
  if (!new_elements)
  {
    cc_error(CC_ENOMEM);
  }
  *capacity = new_capacity;
  *elements = new_elements;
}

struct cc_arraylist
{
  cc_object __parent;
  cc_object** elements;
  size_t size, capacity;
};

static void cc_arraylist_visit(cc_arraylist* self)
{
  if (self->elements)
  {
    for (size_t i = 0, n = cc_arraylist_get_size(self); i < n; ++i)
    {
      cc_object* v = cc_arraylist_get_at(self, i);
      if (!v) continue;
      cc_visit(v);
    }
  }
}

static void cc_arraylist_finalize(cc_arraylist* self)
{
  if (self->elements)
  {
    cc_dealloc(self->elements);
    self->elements = NULL;
  }
}

CC_DEFINE_CLASS(cc_arraylist, cc_object, &cc_arraylist_visit, &cc_arraylist_finalize, NULL, NULL)

cc_arraylist *cc_arraylist_create(size_t capacity)
{
  cc_type* type = CC_DECORATE(cc_arraylist_get_type)();
  cc_arraylist* self = (cc_arraylist*)cc_object_allocate_2(type);

  self->elements = cc_zalloc_a(sizeof(cc_object *), capacity);
  if (!self->elements)
  { cc_j(); }
  self->size = 0;
  self->capacity = capacity;

  return self;
}

size_t cc_arraylist_get_size(cc_arraylist* self)
{
  CC_ASSERT_NOT_NULL(self);
  return self->size;
}

cc_object* cc_arraylist_get_at(cc_arraylist* self, size_t index)
{
  CC_ASSERT_NOT_NULL(self);
  if (index >= self->size)
  {
    cc_error(CC_EINVAL);
  }
  return self->elements[index];
}

void cc_arraylist_append(cc_arraylist* self, cc_object* value)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(value);

  if (self->size == self->capacity)
  {
    grow(&self->elements, &self->size, &self->capacity);
  }
  self->elements[self->size] = value;
  self->size++;
}

void cc_arraylist_prepend(cc_arraylist* self, cc_object* value)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(value);

  if (self->size == self->capacity)
  {
    grow(&self->elements, &self->size, &self->capacity);
  }
  memmove(self->elements + 1, self->elements + 0, sizeof(cc_object*) * self->size);
  self->elements[0] = value;
  self->size++;
}

void cc_arraylist_insert(cc_arraylist* self, size_t index, cc_object* value)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(value);
  if (index > self->size)
  {
    cc_error(CC_EINVAL);
  }

  if (self->size == self->capacity)
  {
    grow(&self->elements, &self->size, &self->capacity);
  }
  if (index == self->size)
  {
    self->elements[self->size] = value;
  }
  else if (index == 0)
  {
    memmove(self->elements + 1, self->elements + 0, sizeof(cc_object*) * self->size);
    self->elements[0] = value;
  }
  else
  {
    memmove(self->elements + index + 1, self->elements + index, sizeof(cc_object*) * (self->size - index));
  }
  self->size++;
}

void cc_arraylist_clear(cc_arraylist* self)
{
  self->size = 0;
}
