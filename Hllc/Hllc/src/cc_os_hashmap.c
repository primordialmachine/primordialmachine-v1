/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os_hashmap.h"

typedef struct _cc_node _cc_node;
struct _cc_node
{
  _cc_node* next;
  size_t hash_value;
  cc_object* key;
  cc_object* value;
};