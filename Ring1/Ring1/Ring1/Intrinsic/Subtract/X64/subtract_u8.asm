_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Subtract two unsigned 8 bit integers.
; CL first operand
; DL second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Subtract_X64_subtract_u8 PROC
  SUB cl, dl   ; cl@1 = cl@0 - dl@0 = x - y
  MOV [r8], cl ; [r8]@1 = cl@2
  SETC al      ; al@3 = carry
  RET          ; RETURN
Ring1_Intrinsic_Subtract_X64_subtract_u8 ENDP

_TEXT ENDS

END
