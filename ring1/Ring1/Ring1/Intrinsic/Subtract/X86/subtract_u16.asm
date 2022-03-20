.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Subtract_X86_subtract_u16(uint16_t x, uint16_t y, uint16_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Subtract_X86_subtract_u16@12 PROC
  SUB cx, dx             ; cx@1 = cx@0 - dx@0 = x - y
  POP DWORD PTR edx      ; pop return address
  POP DWORD PTR eax      ; eax@0 = &z
  PUSH edx               ; push return address
  MOV WORD PTR [eax], cx ; *z@1 = cx@1
  SETC al                ; al@1 = carry
  RET                    ; RETURN
@Ring1_Intrinsic_Subtract_X86_subtract_u16@12 ENDP

_TEXT ENDS

END
