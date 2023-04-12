/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include <stdlib.h>
#include "spectre/_tool.h"

static void run(cc_arraylist* args)
{
  cc_tool* tool = cc_create_spectre_tool();
  tool->run(tool, args);
}

int main(int argc, char** argv)
{
  if (!cc_startup())
  {
    return EXIT_FAILURE;
  }
  cc_jt jt;
  cc_push_jt(&jt);
  if (!setjmp(jt.env))
  {
    cc_arraylist* args = cc_arraylist_create(argc);
    for (int i = 0, n = argc; i < n; ++i)
    {
      cc_cstring* arg = cc_cstring_create(argv[i]);
      cc_arraylist_append(args, (cc_object*)arg);
    }
    run(args);
    cc_pop_jt();
  }
  else
  {
    cc_pop_jt();
  }
  if (cc_get_status())
  {
    cc_shutdown();
    return EXIT_FAILURE;
  }
  cc_shutdown();
  return EXIT_SUCCESS;
}
