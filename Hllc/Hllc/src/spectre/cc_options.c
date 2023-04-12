/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_options.h"


#include "cc_os_arraylist.h"


static const char KEY[] = "cc:spectre:options";

static void visit(cc_options* self)
{
  CC_VISIT(self->source_files);
}

static cc_options* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_options_get_type)();
  cc_options* self = (cc_options*)cc_object_allocate_2(type);

  self->source_files = cc_arraylist_create(8);
  self->target = CC_OPTIONS_TARGET_WINDOWS;
  self->mode = CC_OPTIONS_MODE_BUILD;

  return self;
}

DEFINE_COMPONENT(cc_options, &factory, &visit, NULL)

cc_options_target cc_options_get_target(cc_options* self)
{
  return self->target;
}

void cc_options_set_target(cc_options* self, cc_options_target target)
{
  self->target = target;
}

cc_options_mode cc_options_get_mode(cc_options* self)
{
  return self->mode;
}

void cc_options_set_mode(cc_options *self, cc_options_mode mode)
{
  self->mode = mode;
}

cc_arraylist* cc_options_get_source_files(cc_options* self)
{
  return self->source_files;
}

void cc_options_add_source_file(cc_options* self, cc_cstring* source_file)
{
  cc_arraylist_append(self->source_files, (cc_object *)source_file);
}
