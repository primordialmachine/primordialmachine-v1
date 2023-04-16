#if !defined(RING1_CLASSTYPE_USER_H_INCLUDED)
#define RING1_CLASSTYPE_USER_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Ring1/Object/ClassType.internal.h' directly, include 'Ring1/Object.h' instead.")
#endif


#include "Mkx/Object/MemoryManager.h"
#include "Mkx/Object/ClassType.h"
#include "Mkx/Object/Type.internal.h"


/// @brief Representation of a "class" type.
struct Mkx_ClassType
{
  Mkx_Type __parent;

  /// @brief A pointer to the parent type or a null pointer.
  Mkx_Type* parent;

  /// @brief The size, in Bytes, of an object of this type.
  size_t size;
  /// @brief A pointer to a "destruct" function for objects of this type or a null pointer.
  void (*destruct)(Mkx_Object* object);
  /// @brief The memory manager for objects of this type.
  Mkx_MemoryManager *memoryManager;

  /// @brief A pointer to the dispatch.
  void* dispatch;
  /// @brief The size, in Bytes, of the dispatch of this class type.
  size_t dispatchSize;
  /// @brief A pointer to a "construct dispatch" function or a null pointer.
  Mkx_Object_ConstructDispatchFunction* constructDispatch;
  /// @brief A pointer to a "destruct dispatch" function or a null pointer.
  Mkx_Object_DestructDispatchFunction* destructDispatch;

  struct
  {
    int64_t size;
    InterfaceImplementation* elements;
  } implementations;
  /// @todo We can use a "dispatch table" implementation for the dispatch table and the interface dispatch tables.
  Mkx_Dispatches* interfaceDispatches;
};

/// @brief Get if this class type is already initialized.
/// @param self A pointer to this class type.
/// @return @a true if this class type is initialized, @a false otherwise.
Ring1_CheckReturn() Ring1_NonNull() bool
Mkx_ClassType_isInitialized
  (
    Mkx_ClassType* self
  );

Ring1_CheckReturn() Ring1_NonNull(1, 3) int
Mkx_ClassType_construct
  (
    Mkx_ClassType *self,
    void (*notifyShutdown)(),
    const Mkx_ClassTypeRegistrationInfo *info
  );

Ring1_NonNull() void
Mkx_ClassType_destruct
  (
    Mkx_ClassType* self
  );

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ClassType_ensureInitialized
  (
    Mkx_ClassType* self
  );

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ClassType_ensureUninitialized
  (
    Mkx_ClassType* self
  );

/// @brief Get if a class type @a a is a user of another type @a b.
/// @param a A pointer to the class type.
/// @param b A pointer to the other type.
/// @success <code>*result</code> is assigned @a true if @a a is a user of @a b and is assigned @a false otherwise.
/// @failure <code>*result</code> was not dereferenced.
/// @return @a true if @a a is a user of @a b, @a false otherwise.
/// @remark A class type A is a user of a type B if one of the following conditions apples:
/// - The class type B is the parent class type of A.
/// - The class type A directly implements the interface type B.
Ring1_CheckReturn() int
Mkx_ClassType_isUserOf
  (
    bool *result,
    const Mkx_ClassType *a,
    const Mkx_Type *b
  );


#endif // RING1_CLASSTYPE_USER_H_INCLUDED
