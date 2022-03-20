.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Add_X86_add_s16(int16_t x, int16_t y, int16_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Add_X86_add_s16@12 PROC
    ADD cx, dx               ; cx@1 = cx@0 + dx@0 = x - y
    POP DWORD PTR edx        ; pop return address
    POP DWORD PTR eax        ; eax@0 = &z
    PUSH edx                 ; push return address
    MOV WORD PTR [eax], cx   ; *z@0 = cx@1
    SETO al                  ; al@1 = overflow
    RET                      ; RETURN al@1
@Ring1_Intrinsic_Add_X86_add_s16@12 ENDP

_TEXT ENDS

END
