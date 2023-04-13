.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Multiply_X86_multiply_s8(int8_t x, int8_t y, int8_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Multiply_X86_multiply_s8@12 PROC
  ; Perform multiplication cl * dl such that the product is in ax.
  ; The overflow and carry flags are 1 if an overflow occurs, otherwise they are 0.
  MOV al, cl
  IMUL dl
  ; Store the lower word in *z.
  ; As the address of z is on the stack below the return address, pop the return address, pop the address of z, then push the return address again.
  POP DWORD PTR edx
  POP DWORD PTR ecx
  PUSH edx
  MOV BYTE PTR [ecx], al
  ; Store the carry register value in al. Equivalently, we could use SETO.
  SETC al
  RET
@Ring1_Intrinsic_Multiply_X86_multiply_s8@12 ENDP

_TEXT ENDS

END
