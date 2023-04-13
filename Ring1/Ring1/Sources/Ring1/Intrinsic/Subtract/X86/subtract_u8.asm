.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Subtract_X86_subtract_u8(uint8_t x, uint8_t y, uint8_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Subtract_X86_subtract_u8@12 PROC
  SUB cl, dl             ; cl@1 = cl@0 - dl@0 = x - y
  POP DWORD PTR edx      ; pop return address
  POP DWORD PTR eax      ; eax@0 = &z
  PUSH edx               ; push return address
  MOV BYTE PTR [eax], cl ; [eax]@1 = cl@2
  SETC al                ; al@1 = carry
  RET                    ; RETURN
@Ring1_Intrinsic_Subtract_X86_subtract_u8@12 ENDP

_TEXT ENDS

END
