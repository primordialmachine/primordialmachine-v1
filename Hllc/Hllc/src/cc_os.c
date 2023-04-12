/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "cc_os.h"

#include "Ring1/Memory.h"
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <limits.h>
#include "cc_os_lib.h"
#include "spectre/cc_ascii.h"

static int g_status = CC_SUCCESS;

typedef struct cc_types
{
  size_t sz, cp;
  cc_type** buckets;
} cc_types;

static cc_types* g_types = NULL;

static cc_object* g_objects = NULL;

static cc_jt* g_jts = NULL;

void cc_push_jt(cc_jt* jt)
{
  assert(jt != NULL);
  jt->previous = g_jts;
  g_jts = jt;
}

void cc_pop_jt()
{
  assert(g_jts != NULL);
  g_jts = g_jts->previous;
}

CC_NORETURN() void cc_j()
{
  assert(g_jts != NULL);
  longjmp(g_jts->env, -1);
}

static size_t cc_hash_combine_2(size_t x1, size_t x2)
{
  x1 ^= x2 + 0x9e3779b9 + (x1 << 6) + (x1 >> 2);
  return x1;
}

static size_t cc_hash_combine_3(size_t x1, size_t x2, size_t x3)
{
  return cc_hash_combine_2(cc_hash_combine_2(x1, x2), x3);
}

static cc_type *cc_get_or_create_type(cc_type* parent, size_t object_size, cc_visit_callback_ptr visit, cc_finalize_callback_ptr finalize)
{
  if (object_size < sizeof(cc_object))
  {
    fprintf(stderr, "%s:%d: assertion `%s` failed\n", __FILE__, __LINE__, "object_size >= sizeof(cc_object)");
    g_status = CC_EINVAL;
    return NULL;
  }

  if (parent)
  {
    if (object_size < parent->object_size)
    {
      fprintf(stderr, "%s:%d: assertion `%s` failed\n", __FILE__, __LINE__, "object_size >= parent->object_size");
      g_status = CC_EINVAL;
      return NULL;
    }
  }

  size_t hash_value = cc_hash_combine_2(cc_hash_p((void*)visit), cc_hash_p((void*)finalize));
  hash_value = cc_hash_combine_3(hash_value, cc_hash_p(parent), cc_hash_sz(object_size));
  
  size_t bucket_index = hash_value % g_types-> cp;
  
  for (cc_type* type = g_types->buckets[bucket_index]; NULL != type; type = type->next)
  {
    if (type->hash_value == hash_value && type->parent == parent && type->object_size == object_size && type->visit == visit && type->finalize == finalize)
    {
      return type;
    }
  }

  cc_type* type = cc_alloc(sizeof(cc_type));
  if (!type)
  { return NULL; }
  type->hash_value = hash_value;
  type->object_size = object_size;
  type->visit = visit;
  type->finalize = finalize;
  type->parent = parent;
  type->next = g_types->buckets[bucket_index];
  g_types->buckets[bucket_index] = type;
  g_types->sz++;
  // TODO: Try to grow the hash table if necessary.
  // Do not fail if growing the hash table fails.
  return type;
}

bool cc_startup()
{
  g_status = CC_SUCCESS;
  if (!cc_startup_memory())
  {
    return false;
  }
  if (!cc_startup_hash())
  {
    cc_shutdown_memory();
    return false;
  }
  g_objects = NULL;
  g_types = cc_alloc(sizeof(cc_types));
  if (!g_types)
  {
    cc_shutdown_hash();
    cc_shutdown_memory();
    return false;
  }
  static const size_t DEFAULT_CAPACITY = 8;
  g_types->buckets = cc_alloc_a(sizeof(cc_type*), DEFAULT_CAPACITY);
  if (!g_types->buckets)
  {
    cc_dealloc(g_types);
    g_types = NULL;
    cc_shutdown_hash();
    cc_shutdown_memory();
    return false;
  }
  for (size_t i = 0, n = DEFAULT_CAPACITY; i < n; ++i)
  {
    g_types->buckets[i] = NULL;
  }
  g_types->sz = 0;
  g_types->cp = DEFAULT_CAPACITY;
  return true;
}

void cc_shutdown()
{
  cc_log_memory();

  while (g_objects)
  {
    cc_object* object = g_objects; g_objects = object->next;
    if (object->type)
    {
      cc_type* t = object->type;
      do
      {
        if (t->finalize)
        {
          t->finalize(object);
        }
        t = t->parent;
      } while (t);
    }
    cc_dealloc(object);
  }

  for (size_t i = 0, n = g_types->cp; i < n; ++i)
  {
    while (g_types->buckets[i])
    {
      cc_type* type = g_types->buckets[i]; g_types->buckets[i] = type->next;
      cc_dealloc(type);
      g_types->sz--;
    }
  }
  cc_dealloc(g_types->buckets);
  g_types->buckets = NULL;
  cc_dealloc(g_types);
  g_types = NULL;

  cc_shutdown_hash();
  cc_log_memory();
  cc_shutdown_memory();
}

void cc_visit(cc_object* o)
{
  if (o && o->type)
  {
    cc_type* t = o->type;
    do
    {
      if (t->visit)
      {
        t->visit(o);
      }
      t = t->parent;
    } while (t);
  }
}

static cc_type* CC_DECORATE(cc_object_type) = NULL;

cc_type* CC_DECORATE(cc_object_get_type)()
{
  if (!CC_DECORATE(cc_object_type))
  {
    const cc_type_spec spec = {
      .parent = NULL,
      .object_size = sizeof(cc_object),
      .visit = NULL,
      .finalize = NULL,
    };
    CC_DECORATE(cc_object_type) = cc_type_get_or_create(&spec);
  }
  return CC_DECORATE(cc_object_type);
}

cc_type* cc_type_get_or_create_no_raise(cc_type* parent, size_t object_size, cc_visit_callback_ptr visit, cc_finalize_callback_ptr finalize)
{
  return cc_get_or_create_type(parent, object_size, visit, finalize);
}

cc_type* cc_type_get_or_create(const cc_type_spec *spec)
{
  cc_type* type = cc_get_or_create_type(spec->parent, spec->object_size, spec->visit, spec->finalize);
  if (!type) cc_j();
  return type;
}

cc_object* cc_object_allocate_no_raise_2(cc_type *type)
{
  if (!type)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: assertion `type != NULL` failed\n", __FILE__, __LINE__);
    g_status = CC_EINVAL;
    return NULL;
  }
  cc_object* object = cc_zalloc(type->object_size);
  if (!object)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: allocation of %zu Bytes failed\n", __FILE__, __LINE__, type->object_size);
    return NULL;
  }
  object->type = type;
  object->next = g_objects; g_objects = object;
  return object;
}

cc_object* cc_object_allocate_2(cc_type* type)
{
  CC_ASSERT_NOT_NULL(type);
  cc_object* object = cc_object_allocate_no_raise_2(type);
  if (!object)
  { cc_j(); }
  return object;
}

CC_NORETURN() void cc_error(int status)
{
  cc_set_status(status);
  cc_j();
}

int cc_get_status()
{
  return g_status;
}

void cc_set_status(int status)
{
  g_status = status;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char* cc_asprintf(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int c = _vsnprintf(NULL, 0, fmt, args);
  if (c < 0 || c > INT_MAX - 1)
  {
    g_status = CC_EINVAL;
    return NULL;
  }
  char* w = cc_alloc((size_t)c + 1);
  if (!w)
  {
    g_status = CC_ENOMEM;
    return NULL;
  }
  _vsnprintf(w, (size_t)c + 1, fmt, args);
  return w;
}

char* cc_to_upper(const char* w)
{
  if (!w)
  {
    g_status = CC_EINVAL;
    return NULL;
  }
  char* v = _strdup(w);
  if (!v)
  {
    g_status = CC_ENOMEM;
    return NULL;
  }
  for (size_t i = 0; v[i] != '\0'; i++)
  {
    if (v[i] >= 'a' && v[i] <= 'z')
    {
      v[i] = v[i] - 32;
    }
  }
  return v;
}

char* cc_strdup(const char* w)
{
  if (!w)
  {
    g_status = CC_EINVAL;
    return NULL;
  }
  char *v = _strdup(w);
  if (!v)
  {
    g_status = CC_ENOMEM;
    return NULL;
  }
  return v;
}

int cc_strcmp(const char* v, const char* w)
{
  return strcmp(v, w);
}

void cc_replace_c(char* s, char c1, char c2)
{
  size_t i = 0;
  for (i = 0; s[i]; i++)
  {
    if (s[i] == c1)
    {
      s[i] = c2;
    }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_cstring_finalize(cc_cstring* self)
{
  if (self->p)
  {
    cc_dealloc(self->p);
    self->p = NULL;
  }
}

CC_DEFINE_CLASS(cc_cstring, cc_object, NULL, &cc_cstring_finalize, NULL, NULL)

static char* _cc_cstring_strdup(const char* p)
{
  size_t n = strlen(p);
  char *q = cc_alloc_a(sizeof(char), n + 1);
  if (!q) return NULL;
  strcpy(q, p);
  return q;
}

cc_cstring* cc_cstring_create(const char *p)
{
  CC_ASSERT_NOT_NULL(p);
  cc_type* type = CC_DECORATE(cc_cstring_get_type)();
  cc_cstring* self = (cc_cstring*)cc_object_allocate_2(type);
  self->p = _cc_cstring_strdup(p);
  if (!self->p)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: %s failed\n", __FILE__, __LINE__, "_Strdup");
    cc_j();
  }
  return self;
}

cc_cstring* cc_cstring_create_l(const char* p, size_t n)
{
  CC_ASSERT_NOT_NULL(p);
  size_t count = 0;
  for (size_t i = 0; i < n; ++i)
  {
    if (p[i] == '\0')
    {
      break;
    }
    count++;
  }
  cc_type* type = CC_DECORATE(cc_cstring_get_type)();
  cc_cstring* self = (cc_cstring*)cc_object_allocate_2(type);
  self->p = cc_alloc_a(sizeof(char), count + 1);
  if (!self->p)
  { cc_j(); }
  memcpy(self->p, p, count);
  self->p[count] = '\0';
  return self;
}

cc_cstring* cc_cstring_to_upper(cc_cstring* x)
{
  CC_ASSERT_NOT_NULL(x);
  cc_type* type = CC_DECORATE(cc_cstring_get_type)();
  cc_cstring* y = (cc_cstring *)cc_object_allocate_2(type);
  y->p = _cc_cstring_strdup(x->p);
  if (!y->p)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: %s failed\n", __FILE__, __LINE__, "_Strdup");
    cc_j();
  }
  for (size_t i = 0; y->p[i] != '\0'; ++i)
  {
    if (y->p[i] >= 'a' && y->p[i] <= 'z')
    {
      y->p[i] = y->p[i] - 32;
    }
  }
  return y;
}

bool cc_cstring_equal(cc_cstring const* const x, cc_cstring const* const y)
{
  CC_ASSERT_NOT_NULL(x);
  CC_ASSERT_NOT_NULL(y);
  if (x == y)
  {
    return true;
  }
  return !cc_strcmp(x->p, y->p);
}

size_t cc_cstring_get_length(cc_cstring const* const self)
{
  CC_ASSERT_NOT_NULL(self);
  return strlen(self->p);
}

cc_arraylist* cc_cstring_split(cc_cstring const* const self, char separator, cc_arraylist* list)
{
  CC_ASSERT_NOT_NULL(self);
  if (separator == '\0')
  {
    cc_error(CC_EINVAL);
  }

  if (list == NULL)
  {
    list = cc_arraylist_create(8);
  }

  const char* start = self->p, * current = self->p;

  while (*current != '\0')
  {
    if (*current == separator)
    {
      // Do we have anything to copy at all?
      if (current != start)
      {
        cc_cstring* element = cc_cstring_create_l(start, current - start);
        cc_arraylist_append(list, (cc_object*)element);
      }
      // Continue after separator.
      current++;
      start = current;
    }
    else
    {
      current++;
    }
  }
  // Do we have anything to copy at all?
  if (current != start)
  {
    cc_cstring* element = cc_cstring_create_l(start, current - start);
    cc_arraylist_append(list, (cc_object*)element);
  }
  return list;
}

bool cc_cstring_ends_with(cc_cstring const* string, cc_cstring const* suffix) {
  size_t string_length = cc_cstring_get_length(string);
  size_t suffix_length = cc_cstring_get_length(suffix);
  if (suffix_length == 0) return true;
  else if (suffix_length > string_length) return false;
  int temporary;
  Ring1_Memory_compare(&temporary,
                       suffix->p,
                       suffix_length,
                       string->p,
                       string_length,
                       Ring1_Memory_Compare_Lexicographic);
  return !temporary;
}

cc_cstring *cc_cstring_concatenate(cc_cstring const* prefix, cc_cstring const* suffix) {
  CC_ASSERT_NOT_NULL(prefix);
  CC_ASSERT_NOT_NULL(suffix);
  cc_type* type = CC_DECORATE(cc_cstring_get_type)();
  cc_cstring* self = (cc_cstring*)cc_object_allocate_2(type);
  size_t prefix_l = cc_cstring_get_length(prefix);
  size_t suffix_l = cc_cstring_get_length(suffix);
  if (SIZE_MAX - prefix_l <= suffix_l) /*lower than or equal to take into accoun the zero terminator */ {
    cc_error(CC_EINVAL);
  }
  self->p = cc_alloc_a(sizeof(char), prefix_l + suffix_l + 1);
  if (!self->p) {
    cc_error(CC_ENOMEM);
  }
  memcpy(self->p, prefix->p, prefix_l);
  memcpy(self->p + prefix_l, suffix->p, suffix_l);
  self->p[prefix_l + suffix_l] = '\0';
  return self;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
