#if !defined(MKX_OBJECT_INTERFACEIMPLEMENTATION_H_INCLUDED)
#define MKX_OBJECT_INTERFACEIMPLEMENTATION_H_INCLUDED

// Forward declaration.
typedef struct Mkx_InterfaceType Mkx_InterfaceType;
typedef struct Mkx_Interface_Dispatch Mkx_Interface_Dispatch;

/// @brief
/// If a class type A implements an interface type I,
/// then an interface implementation is added to A.
typedef struct InterfaceImplementation
{

  /// @brief The implemented interface.
  Mkx_InterfaceType *interface;

  /// The interface implementation constructor. Can be null.
  void (*construct)(Mkx_Interface_Dispatch *dispatch);

} InterfaceImplementation;

#endif // MKX_OBJECT_INTERFACEIMPLEMENTATION_H_INCLUDED
