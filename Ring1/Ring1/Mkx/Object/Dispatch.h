#if !defined(RING1_OBJECT_DISPATCH_H_INCLUDED)
#define RING1_OBJECT_DISPATCH_H_INCLUDED

#include "Ring1/Intrinsic/_Include.h"
#include <stdbool.h>
typedef struct Mkx_Type Mkx_Type;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MKX_DISPATCH(pointer) ((Mkx_Dispatch *)(pointer))
typedef struct Mkx_Dispatch Mkx_Dispatch;

/// @brief The base of all dispatch (table).
struct Mkx_Dispatch {
  Mkx_Type *type;
};

/// @brief Create a dispatch.
/// @param result A pointer to an <code>Mkx_Dispatch *</code> variable.
/// @param type A pointer to an interface type.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @success <code>*result</code> was assigned a pointer to the dispatch.
/// @failure <code>result</code> was not dereferenced.
/// @todo Aside of interface types, support class types. 
Ring1_CheckReturn() int
Mkx_Dispatch_create
  (
    Mkx_Dispatch **result,
    Mkx_Type *type
  );

/// @brief Clone a dispatch.
/// @param result A pointer to an <code>Mkx_Dispatch *</code> variable.
/// @param self A pointer to the dispatch.
/// @return@a 0 on success, a non-zero value on failure.
/// @success <code>*result</code> was assigned a pointer to the clone of the dispatch.
/// @failure <code>result</code> was not dereferenced.
Ring1_CheckReturn() int 
Mkx_Dispatch_clone
  (
    Mkx_Dispatch **result,
    Mkx_Dispatch *self
  );

/// @brief Destroy a dispatch.
/// @param self A pointer to the dispatch.
void
Mkx_Dispatch_destroy
  (
    Mkx_Dispatch *self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MKX_DISPATCHES(pointer) ((Mkx_Dispatches *)(pointer))
typedef struct Mkx_Dispatches Mkx_Dispatches;

struct Mkx_Dispatches
{
  int64_t size;
  Mkx_Dispatch** elements;
};

Ring1_CheckReturn() int
Mkx_Dispatches_getOrCreateEntry
  (
    int64_t* result,
    Mkx_Dispatches* self,
    Mkx_Type* type,
    bool create
  );

Ring1_CheckReturn() int
Mkx_Dispatches_getEntryAt
  (
    Mkx_Dispatch** result,
    Mkx_Dispatches* self,
    int64_t index
  );

Ring1_CheckReturn() int
Mkx_Dispatches_clone
  (
    Mkx_Dispatches** result,
    Mkx_Dispatches* self
  );

Ring1_CheckReturn() int
Mkx_Dispatches_create
  (
    Mkx_Dispatches** result
  );

Ring1_CheckReturn() int
Mkx_Dispatches_destroy
  (
    Mkx_Dispatches* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // RING1_OBJECT_DISPATCH_H_INCLUDED
