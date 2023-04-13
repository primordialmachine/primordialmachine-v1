#if !defined(RING1_TYPEDESCRIPTOR_H_INCLUDED)
#define RING1_TYPEDESCRIPTOR_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_Module_Declare(Ring1, TypeDescriptor)

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct Ring1_TypeDescriptor Ring1_TypeDescriptor;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/// @brief Descriptor of a scalar type.
/// Scalar types are
/// - boolean (<code>Boolean</code>),
/// - integer-number (<code>Integer(8|16|32|64)?</code>),
/// - natural-number (<code>Natural(8|16|32|64)?</code>), and
/// - real-number (<code>Real(32|64)?</code>)
/// types.
/// Can be safely cast into a <code>Ring1_TypeDescriptor</code> object.
typedef struct Ring1_ScalarTypeDescriptor Ring1_ScalarTypeDescriptor;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// Built-in scalar types.

/// @brief Get the type descriptor of the <code>Boolean</code> type.
/// @param result A pointer to a <code>Ring1_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getBoolean
  (
    Ring1_ScalarTypeDescriptor **result
  ); 
  
/// @brief Get the type descriptor of the <code>Integer</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getInteger
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Integer8</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getInteger8
  (
  );
  
/// @brief Get the type descriptor of the <code>Integer16</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getInteger16
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Integer32</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getInteger32
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Integer64</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getInteger64
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Natural</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getNatural
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Natural8</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getNatural8
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Natural16</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getNatural16
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Natural32</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getNatural32
  (
  );

/// @brief Get the type descriptor of the <code>Natural64</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object. 
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getNatural64
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Real32</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getReal32
  (
    Ring1_ScalarTypeDescriptor **result
  );
  
/// @brief Get the type descriptor of the <code>Real64</code> type.
/// @param result A pointer to a <code>Ring1_X_ScalarTypeDescriptor *</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @post <code>*result</code> was assigned a pointer to a <code>Ring1_X_ScalarTypeDescriptor</code> object.
Ring1_CheckReturn() Ring1_Result
Ring1_X_ScalarTypeDescriptor_getReal64
  (
    Ring1_ScalarTypeDescriptor **result
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#endif // RING1_TYPEDESCRIPTOR_H_INCLUDED
