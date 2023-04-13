.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Multiply_X86_multiply_u16(uint16_t x, uint16_t y, uint16_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Multiply_X86_multiply_u16@12 PROC
  ; Perform multiplication cx * dx such that the lower word of the product is in ax and the higher word in dx.
  ; The overflow and carry flags are 1 if an overflow occurs, otherwise they are 0.
  MOV ax, cx  
  MUL dx
  ; Store the lower word in *z.
  ; As the address of z is on the stack below the return address, pop the return address, pop the address of z, then push the return address again.
  POP DWORD PTR edx
  POP DWORD PTR ecx
  PUSH edx
  MOV WORD PTR [ecx], ax
  ; Store the carry register value in al. Equivalently, we could use SETO.
  SETC al
  RET
@Ring1_Intrinsic_Multiply_X86_multiply_u16@12 ENDP

_TEXT ENDS

END
