/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_context.h"


#include "cc_os_lib.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct cc_ctx_entry
{
  cc_object parent;
  const char *key;
  cc_object* instance;
};

static void cc_ctx_entry_visit(cc_ctx_entry* self)
{
  CC_VISIT(self->instance);
}

CC_DEFINE_CLASS(cc_ctx_entry, cc_object, &cc_ctx_entry_visit, NULL, NULL, NULL)

cc_ctx_entry* cc_ctx_entry_create(const char *key, cc_object* instance)
{
  cc_type* type = CC_DECORATE(cc_ctx_entry_get_type)();
  cc_ctx_entry* self = (cc_ctx_entry*)cc_object_allocate_2(type);

  self->key = key;
  self->instance = instance;

  return self;
}

static void cc_ctx_visit(cc_ctx* self)
{
  CC_VISIT(self->instances);
}

CC_DEFINE_CLASS(cc_ctx, cc_object, &cc_ctx_visit, NULL, NULL, NULL)

cc_ctx* cc_ctx_create()
{
  cc_type* type = CC_DECORATE(cc_ctx_get_type)();
  cc_ctx* ctx = (cc_ctx*)cc_object_allocate_2(type);

  ctx->instances = cc_arraylist_create(0);

  return ctx;
}

static cc_ctx_entry* get_by_key(cc_ctx* self, const char *key)
{
  for (size_t i = 0, n = cc_arraylist_get_size(self->instances); i < n; ++i)
  {
    cc_ctx_entry* entry = (cc_ctx_entry*)cc_arraylist_get_at(self->instances, i);
    if (entry->key == key)
    {
      return entry;
    }
  }
  return NULL;
}

void cc_ctx_add_instance(cc_ctx *self, const char *key, cc_object* instance)
{
  cc_ctx_entry* entry = get_by_key(self, key);
  if (entry)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_INTERNAL, "%s:%d: an instance for key '%s' already exists\n", __FILE__, __LINE__, key);
    cc_error(CC_EINVAL);
  }
  cc_arraylist_append(self->instances, (cc_object *)cc_ctx_entry_create(key, instance));
}

cc_object* cc_ctx_get_instance(cc_ctx* self, const char *key)
{
  cc_ctx_entry* entry = get_by_key(self, key);
  if (!entry)
  { return NULL; }
  return entry->instance;
}
