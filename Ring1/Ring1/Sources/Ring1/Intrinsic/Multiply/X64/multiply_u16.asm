_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Multiply two unsigned 16 bit integers.
; CX = first operand
; DX = second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Multiply_X64_multiply_u16 PROC
  ; Perform multiplication cx * dx such that the lower word of the product is in ax and the higher word in dx.
  ; The overflow and carry flags are 1 if an overflow occurs, otherwise they are 0.
  MOV ax, cx
  MUL dx
  ; Store result in *z.
  MOV [r8], ax
  ; Store the carry register value in al. Equivalently, we could use SETO.
  SETC al
  RET
Ring1_Intrinsic_Multiply_X64_multiply_u16 ENDP

_TEXT ENDS

END
