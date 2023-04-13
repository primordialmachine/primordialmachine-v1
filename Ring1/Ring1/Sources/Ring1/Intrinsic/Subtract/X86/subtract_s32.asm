.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Subtract_X86_subtract_s32(int32_t x, int32_t y, int32_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Subtract_X86_subtract_s32@12 PROC
  SUB ecx, edx              ; ecx@1 = ecx@0 - edx@0 = x - y.
  POP DWORD PTR edx         ; pop return address
  POP DWORD PTR eax         ; eax@0 = &z
  PUSH edx                  ; push return address
  MOV DWORD PTR [eax], ecx  ; *z@0 = ecx@1
  SETO al                   ; al@1 = overflow
  RET                       ; RETURN
@Ring1_Intrinsic_Subtract_X86_subtract_s32@12 ENDP

_TEXT ENDS

END
