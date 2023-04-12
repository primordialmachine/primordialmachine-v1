/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_names.h"


static const char KEY[] = "cc:spectre:names";

static void cc_spectre_names_visit(cc_spectre_names* self)
{
  CC_VISIT(self->names);

#define DEFINE(NAME, STRING) \
  if (self->NAME) \
  { \
    cc_visit((cc_object *)self->NAME); \
  }

#include "spectre/cc_names.i"

#undef DEFINE
}

static void cc_spectre_names_finalize(cc_spectre_names* self)
{ }

static cc_spectre_names* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_spectre_names_get_type)();
  cc_spectre_names* self = (cc_spectre_names*)cc_object_allocate_2(type);

  self->names = cc_names_get_instance(ctx);
  
#define DEFINE(NAME, STRING) \
  self->NAME = cc_names_get_or_create(self->names, STRING);

#include "spectre/cc_names.i"

#undef DEFINE
  
  return self;
}

DEFINE_COMPONENT(cc_spectre_names, &factory, &cc_spectre_names_visit, &cc_spectre_names_finalize)

cc_name* cc_spectre_names_get_or_create(cc_spectre_names* self, const char* p)
{
  return cc_names_get_or_create(self->names, p);
}
