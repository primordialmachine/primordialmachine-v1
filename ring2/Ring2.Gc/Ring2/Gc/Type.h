// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/Type.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_GC_TYPE_H_INCLUDED)
#define RING2_GC_TYPE_H_INCLUDED

// Forward declaration.
typedef void Ring2_Gc;

/// Type of a "visit" callback function for GC objects.
/// @param gc The GC.
/// @param object The object to visit.
typedef void (Ring2_Gc_VisitCallback)(Ring2_Gc* gc, void*);

/// Type of a "finalize" callback function for GC objects.
/// @param gc The GC.
/// @param object The object to finalize.
typedef void (Ring2_Gc_FinalizeCallback)(Ring2_Gc* gc, void*);

typedef struct Ring2_Gc_Type
{

  /// @brief A pointer to a Mkx_Gc_FinalizeCallback function or a null pointer.
  Ring2_Gc_FinalizeCallback* finalize;

  /// @brief A pointer to a Mkx_Gc_VisitCallback function or a null pointer.
  Ring2_Gc_VisitCallback* visit;

} Ring2_Gc_Type;

#endif // RING2_GC_TYPE_H_INCLUDED
