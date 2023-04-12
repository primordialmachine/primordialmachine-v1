/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_names.h"


#include <string.h>


static void cc_name_visit(cc_name* self)
{
  CC_VISIT(self->string);
}

cc_name* cc_name_create(cc_cstring* string, size_t hash_value)
{
  cc_type* type = CC_DECORATE(cc_name_get_type)();
  cc_name* self = (cc_name*)cc_object_allocate_2(type);

  self->hash_value = hash_value;
  self->string = string;

  return self;
}

CC_DEFINE_CLASS(cc_name, cc_object, NULL, NULL, NULL, NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const char KEY[] = "cc:names";

static void cc_names_visit(cc_names* self)
{
  for (size_t i = 0, n = self->capacity; i < n; ++i)
  {
    for (cc_name* name = self->buckets[i]; name != NULL; name = name->next)
    {
      cc_visit((cc_object*)name);
    }
  }
}

static void cc_names_finalize(cc_names* self)
{
  if (self->buckets)
  {
    cc_dealloc(self->buckets);
    self->buckets = NULL;
  }
}

static cc_names* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_names_get_type)();
  cc_names* self = (cc_names*)cc_object_allocate_2(type);

  self->size = 0;
  self->capacity = 8;
  self->buckets = cc_alloc_a(sizeof(cc_name*), 8);
  for (size_t i = 0, n = 8; i < n; ++i)
  {
    self->buckets[i] = NULL;
  }

  return self;
}

DEFINE_COMPONENT(cc_names, &factory, &cc_names_visit, &cc_names_finalize)

cc_name* cc_names_get_or_create(cc_names* self, const char* p)
{
  size_t length = strlen(p);
  size_t hash_value = cc_hash_a(p, strlen(p));
  size_t bucket_index = hash_value % self->capacity;

  for (cc_name* name = self->buckets[bucket_index]; name != NULL; name = name->next)
  {
    if (name->hash_value == hash_value && cc_cstring_get_length(name->string) == length && !memcmp(name->string->p, p, length))
    {
      return name;
    }
  }
  cc_name* name = cc_name_create(cc_cstring_create(p), hash_value);
  name->next = self->buckets[bucket_index];
  self->buckets[bucket_index] = name;
  self->size++;
  return name;
}
