
static inline void
getTwo
  (
    Ring2_Context* context,
    Ring2_Value **x,
    Ring2_Value **y
  )
{ 
  // Assert the 2nd operand exists and get the 2nd operand.
  Ring2_Value *b = Mkx_Interpreter_Stack_getAt(context, 0);
  if (!b) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  
  // Get the 1st operand exists and get the 1st operand.
  Ring2_Value* a = Mkx_Interpreter_Stack_getAt(context, 1);
  if (!a) { 
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  
  *y = b;
  *x = a;
}
