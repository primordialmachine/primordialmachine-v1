// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/Object.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

/// @brief Utilities for defining typical reference counted objects.
#if !defined(MKX_OBJECT_OBJECT_H_INCLUDED)
#define MKX_OBJECT_OBJECT_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/Object.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/MemoryManager.h"
#include "Mkx/Object/Types.h"
#include "Mkx/Object/Dispatch.h"
#include "Ring1/Status.h"
typedef struct Mkx_WeakReference Mkx_WeakReference;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Mkx_Type*
__Mkx_Object_getType__
  (
  );

typedef struct Mkx_Object Mkx_Object;

static inline Mkx_Object *
MKX_OBJECT
  (
    void *pointer
  )
{ return (Mkx_Object*)pointer; }

typedef struct Mkx_Object_Dispatch Mkx_Object_Dispatch;

static inline Mkx_Object_Dispatch *
MKX_OBJECT_DISPATCH
  (
    void *pointer
  )
{ return (Mkx_Object_Dispatch*)pointer; }

struct Mkx_Object
{
  Ring1_ReferenceCounter referenceCount;
  Mkx_Type* type;
  
  /// @brief Pointer to the list of weak references to this object or a null pointer.
  /// @todo Should not be part of the public API.
  Mkx_WeakReference* weakReferences;

  /// @brief When an object of class type X is allocated,
  /// then the type of the object is not necessarily type
  /// X when it is deallocated but ancestor class type Y
  /// of X.
  ///
  /// For example, this is the case when the constructors fail.
  ///
  /// Consequently, we need to store the memory manager of type X directly after allocation of the object.
  /// @todo Should not be part of the public API.
  Mkx_MemoryManager* memoryManager;
};

struct Mkx_Object_Dispatch
{
  Mkx_Dispatch parent;
  Ring1_Status (*equalTo)(bool* result, Mkx_Object* self, Mkx_Object* other);
  Ring1_Status(*notEqualTo)(bool* result, Mkx_Object* self, Mkx_Object* other);
  Ring1_Status(*hashValue)(int64_t* result, Mkx_Object* self);
};

Ring1_NonNull() Mkx_Type*
Mkx_Object_getType
  (
    const Mkx_Object* self
  );

Ring1_CheckReturn() Ring1_Status
Mkx_Object_construct
  (
    Mkx_Object* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NonNull() void
Mkx_Object_reference
  (
    Mkx_Object* self
  );

Ring1_NonNull() void
Mkx_Object_unreference
  (
    Mkx_Object* self
  );

Ring1_CheckReturn() Ring1_NonNull() Ring1_ReferenceCounter
Mkx_Object_getReferences
  (
    Mkx_Object* self
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_object_equalto
Ring1_CheckReturn() Ring1_Status
Mkx_Object_equalTo
  (
    bool *result,
    Mkx_Object *self,
    Mkx_Object *other
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_object_notequalto
Ring1_CheckReturn() Ring1_Status
Mkx_Object_notEqualTo
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Object* other
  );

// https://documentation.primordialmachine.com/utility-libraries/object-library#mkx_object_hashvalue
Ring1_CheckReturn() Ring1_Status
Mkx_Object_hashValue
  (
    int64_t* result,
    Mkx_Object* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @todo Use procedure style.
Ring1_CheckReturn() void*
Mkx_Object_allocate
  (
    Mkx_Type* type
  );

/// @brief Get if an object is an instance of the specified type.
/// @param result A pointer to a <code>bool</code> variable.
/// @param object A pointer to the object.
/// @param type A pointer to the type.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_CheckReturn() Ring1_Status
Mkx_Object_isInstanceOf
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Type* type
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @deprecated Use MKX_OBJECTCLASSMETHODCALLBODY
#define MKX_VIRTUALCALLBODY(T, F, ...) MKX_OBJECTCLASSMETHODCALLBODY(T, F, __VA_ARGS__)

Ring1_CheckReturn() Ring1_Status
Mkx_Invocation_getDispatch
  (
    void** result,
    Mkx_Object* object,
    Mkx_Type* type
  );

/// @brief Utility macro to define the body of object class method calls.
/// @code
/// MKX_OBJECTCLASSMETHODCALLBODY(A, f, x0, self, x1)
/// @endcode
/// is equivalent to
/// @code
/// void *dispatch; \
/// if (Ring1_Unlikely(Mkx_Invocation_getClassDispatch(&dispatch, MKX_OBJECT(self), NULL))) return 1; \
/// return ((A##_Dispatch *)(dispatch))->f(x0, self, x1);
/// @endcode
#define MKX_OBJECTCLASSMETHODCALLBODY(T, F, ...) \
  void *dispatch; \
  if (Ring1_Unlikely(Mkx_Invocation_getDispatch(&dispatch, MKX_OBJECT(self), NULL))) return 1; \
  return ((T##_Dispatch *)(dispatch))->F(__VA_ARGS__);

/// @brief Utility macro to define the body of object interface method calls.
/// @code
/// MKX_OBJECTINTERFACECALLMETHODBODY(A, f, x0, self, x1)
/// @endcode
/// is equivalent to
/// @code
/// void* dispatch; \
/// if (Ring1_Unlikely(Mkx_Invocation_GetInterfaceDispatch(&dispatch, MKX_OBJECT(self), MKX_TYPE_GET(A)))) return 1; \
/// return ((A##_Dispatch*)(dispatch))->f(x0, self, x1);
/// @endcode
#define MKX_OBJECTINTERFACECALLMETHODBODY(T, F, ...) \
  void *dispatch; \
  if (Ring1_Unlikely(Mkx_Invocation_getDispatch(&dispatch, MKX_OBJECT(self), MKX_TYPE_GET(T)))) return 1; \
  return ((T##_Dispatch *)(dispatch))->F(__VA_ARGS__);

/// @brief Utiltiy macro to declare a default constructor.
/// @param CNAME The C name of the type e.g. <code>Mkx_Scene_Viewport</code>.
#define MKX_DEFAULTCONSTRUCTORDECLARATION(CNAME) \
  Ring1_CheckReturn() Ring1_Status \
  CNAME##_constructDefault \
    ( \
      CNAME *self \
    );

/// @brief Utiltiy macro to declare a default creator.
/// @param CNAME The C name of the type e.g. <code>Mkx_Scene_Viewport</code>.
#define MKX_DEFAULTCREATORDECLARATION(CNAME) \
  Ring1_CheckReturn() Ring1_Status \
  CNAME##_createDefault \
    ( \
      CNAME **result \
    );

/// @brief Utility macro to define a default creator.
/// @param CNAME The C name of the type e.g. <code>Mkx_Scene_Viewport</code>.
#define MKX_DEFAULTCREATORDEFINITION(CNAME) \
  Ring1_CheckReturn() Ring1_Status \
  CNAME##_createDefault \
    ( \
      CNAME **result \
    ) \
  { \
    Mkx_Type* type = MKX_TYPE_GET(CNAME); \
    if (Ring1_Unlikely(!type)) return 1; \
    CNAME* self = Mkx_Object_allocate(type); \
    if (Ring1_Unlikely(!self)) return 1; \
    if (Ring1_Unlikely(CNAME##_constructDefault(self))) \
    { \
      Mkx_Object_unreference(MKX_OBJECT(self)); \
      return 1; \
    } \
    *result = self; \
    return Ring1_Status_Success; \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NonNull(1) static inline void
__setObjectField__
  (
    Mkx_Object * *field,
    Mkx_Object * value
  )
{
  if (Ring1_Likely(*field != value))
  {
    if (value) Mkx_Object_reference(value);
    if (*field) Mkx_Object_unreference(*field);
    *field = value;
  }
}

/// @brief Macro to set the value of an Mkx_Object * or derived type field
/// to an Mkx_Object * or derived type value.
/// @param FIELD The field name.
/// @param VALUE The value.
/// @code
/// MKX_SETOBJECTFIELD(field, value)
/// @endcode
/// evaluates to
/// @code
/// { __setObjectField__((Mkx_Object **)&(field), (Mkx_Object *)value); }
/// @endcode
#define MKX_SETOBJECTFIELD(FIELD, VALUE) \
{ __setObjectField__((Mkx_Object **)&(FIELD), (Mkx_Object *)VALUE); }

#endif // MKX_OBJECT_OBJECT_H_INCLUDED
