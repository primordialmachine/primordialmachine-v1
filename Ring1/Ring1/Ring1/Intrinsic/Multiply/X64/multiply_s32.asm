_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Multiply two signed 32 bit integers.
; ECX = first operand
; EDX = second operand
; R8 = pointer to the result variable
Ring1_Intrinsic_Multiply_X64_multiply_s32 PROC
  ; Perform multiplication ecx * edx such that the lower word of the product is in eax and the higher word is in edx.
  ; The overflow and carry flags are 1 if an overflow occurs, otherwise they are 0.
  MOV eax, ecx
  IMUL edx
  ; Store result in *z.
  MOV [r8], eax
  ; Store the carry register value in al. Equivalently, we could use SETO.
  SETC al
  RET
Ring1_Intrinsic_Multiply_X64_multiply_s32 ENDP

_TEXT ENDS

END