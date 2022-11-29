_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Subtract two unsigned 64 bit integers.
; RCX = first operand
; RDX = second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Subtract_X64_subtract_u64 PROC
  SUB rcx, rdx  ; rcx@1 = rcx@0 - rdx@0 = x - y 
  MOV [r8], rcx ; [r8]@1 = rcx@1
  SETC al       ; al@1 = carry
  RET           ; RETURN
Ring1_Intrinsic_Subtract_X64_subtract_u64 ENDP

_TEXT ENDS

END
