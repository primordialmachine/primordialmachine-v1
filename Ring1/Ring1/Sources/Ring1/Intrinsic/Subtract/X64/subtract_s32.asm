_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Subtract two signed 32 bit integers.
; ECX = first operand
; EDX = second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Subtract_X64_subtract_s32 PROC
  SUB ecx, edx  ; ecx@1 = ecx@0 - edx@0 = x - y
  MOV [r8], ecx ; [r8]@1 = ecx@1
  SETO al       ; al@3 = overflow
  RET           ; RETURN AL@2
Ring1_Intrinsic_Subtract_X64_subtract_s32 ENDP

_TEXT ENDS

END
