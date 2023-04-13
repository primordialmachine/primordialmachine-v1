_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Subtract two signed 64 bit integers.
; ECX = first operand
; EDX = second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Subtract_X64_subtract_s64 PROC
  SUB rcx, rdx  ; rcx@1 = rcx@0 - rdx@0 = x - y
  MOV [r8], rcx ; [r8]@1 = rcx@1
  SETO al       ; al@1 = overflow
  RET           ; RETURN
Ring1_Intrinsic_Subtract_X64_subtract_s64 ENDP

_TEXT ENDS

END
