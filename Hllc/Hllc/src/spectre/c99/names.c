/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/c99/names.h"


static const char KEY[] = "spectre:c99:names";

static void cc_c99_names_visit(cc_c99_names* self)
{
  CC_VISIT(self->names);

#define DEFINE(NAME, STRING) \
  if (self->NAME) \
  { \
    cc_visit((cc_object *)self->NAME); \
  }

#include "spectre/c99/names.i"

#undef DEFINE
}

static void cc_c99_names_finalize(cc_c99_names* self)
{ }

static cc_c99_names* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_c99_names_get_type)();
  cc_c99_names* self = (cc_c99_names*)cc_object_allocate_2(type);

  self->names = cc_names_get_instance(ctx);
  
#define DEFINE(NAME, STRING) \
  self->NAME = cc_names_get_or_create(self->names, STRING);

#include "spectre/c99/names.i"

#undef DEFINE
  
  return self;
}

DEFINE_COMPONENT(cc_c99_names, &factory, &cc_c99_names_visit, &cc_c99_names_finalize)

cc_name* cc_c99_names_get_or_create(cc_c99_names* self, const char* p)
{
  return cc_names_get_or_create(self->names, p);
}
