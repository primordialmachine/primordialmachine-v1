_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Multiply two signed 8 bit integers.
; CL first operand
; DL second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Multiply_X64_multiply_s8 PROC
  ; Perform multiplication cl * dl such that the product is in ax.
  ; The overflow and carry flags are 1 if an overflow occurs, otherwise they are 0.
  MOV al, cl
  IMUL dl
  ; Store result in *z.
  MOV [r8], al
  ; Store the carry register value in al. Equivalently, we could use SETO.
  SETC al
  RET
Ring1_Intrinsic_Multiply_X64_multiply_s8 ENDP

_TEXT ENDS

END
