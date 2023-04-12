/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_CONTEXT_H_INCLUDED)
#define CC_CONTEXT_H_INCLUDED


#include "cc_os.h"

// Forward declaration.
typedef struct cc_syms cc_syms;
typedef struct cc_enter cc_enter;
typedef struct cc_resolve cc_resolve;
typedef struct cc_emit cc_emit;

typedef struct cc_ctx_entry cc_ctx_entry;



/// @brief Represents a compiler instance.
/// @extends cc_object
CC_DECLARE_CLASS(cc_ctx, cc_object)

struct cc_ctx
{
  cc_object __parent;

  /// @brief List of instance factories/
  cc_arraylist* instances;
};

/// @brief Create a context.
/// @return The context.
cc_ctx* cc_ctx_create();

/* Add an instance for the specified key. @error an instance for the specified key exists. */
void cc_ctx_add_instance(cc_ctx* self, const char* key, cc_object* instance);

/* Get the instance of the specified key. Null if no instance for the specified key exists. */
cc_object* cc_ctx_get_instance(cc_ctx* self, const char *key);

// Macro to forward declare a component.
#define FORWARD_DECLARE_COMPONENT(NAME) \
  CC_FORWARD_DECLARE_CLASS(NAME)

// Macro to begin the declaration of a component.
#define BEGIN_DECLARE_COMPONENT(NAME) \
  CC_DECLARE_CLASS(NAME, cc_object) \
\
  struct NAME \
  { \
    cc_object parent; \
\
    cc_ctx* ctx;

/// Macro to end the declaration of a component.
#define END_DECLARE_COMPONENT(NAME) \
  }; \
\
  NAME* NAME##_get_instance(cc_ctx* ctx);

// Macro to define a component.
#define DEFINE_COMPONENT(NAME, FACTORY, VISIT, FINALIZE) \
  CC_DEFINE_CLASS(NAME, cc_object, VISIT, FINALIZE, NULL, NULL) \
  NAME* NAME##_get_instance(cc_ctx* ctx) \
  { \
    if (!ctx) \
    { cc_error(CC_EINVAL); } \
    NAME* self = (NAME *)cc_ctx_get_instance(ctx, KEY); \
    if (!self) \
    { \
      self = (*FACTORY)(ctx); \
      self->ctx = ctx; \
      cc_ctx_add_instance(ctx, KEY, (cc_object*)self); \
    } \
    return self; \
  }

#endif // CC_CONTEXT_H_INCLUDED
