_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Subtract two unsigned 32 bit integers.
; ECX = first operand
; EDX = second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Subtract_X64_subtract_u32 PROC
  SUB ecx, edx  ; edx@1 = ecx@0 + edx@0
  MOV [r8], ecx ; [r8]@1 = ecx@1
  SETC al       ; al@1 = carry
  RET           ; RETURN
Ring1_Intrinsic_Subtract_X64_subtract_u32 ENDP

_TEXT ENDS

END
