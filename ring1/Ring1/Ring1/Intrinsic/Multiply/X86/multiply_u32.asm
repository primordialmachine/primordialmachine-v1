.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Multiply_X86_multiply_u32(uint32_t x, uint32_t y, uint32_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Multiply_X86_multiply_u32@12 PROC
  ; Perform multiplication ecx * edx such that the lower word of the product is in eax and the higher word in edx.
  ; The overflow and carry flags are 1 if an overflow occurs, otherwise they are 0.
  MOV eax, ecx
  MUL edx
  ; Store the lower word in *z.
  ; As the address of z is on the stack below the return address, pop the return address, pop the address of z, then push the return address again.
  POP DWORD PTR edx
  POP DWORD PTR ecx
  PUSH edx
  MOV DWORD PTR [ecx], eax
  ; Store the carry register value in al. Equivalently, we could use SETO.
  SETC al
  RET
@Ring1_Intrinsic_Multiply_X86_multiply_u32@12 ENDP

_TEXT ENDS

END
