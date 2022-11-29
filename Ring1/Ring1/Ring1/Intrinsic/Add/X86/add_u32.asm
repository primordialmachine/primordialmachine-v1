.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Add_X86_add_u32(uint32_t x, uint32_t y, uint32_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Add_X86_add_u32@12 PROC
    ADD ecx, edx             ; ecx@1 = exc@0 + edx@0 = x + y
    POP DWORD PTR edx        ; pop return address
    POP DWORD PTR eax        ; eax@0 = &z
    PUSH edx                 ; push return address
    MOV DWORD PTR [eax], ecx ; *z@0 = ecx@1
    SETC al                  ; al@1 = carry
    RET                      ; RETURN
@Ring1_Intrinsic_Add_X86_add_u32@12 ENDP

_TEXT ENDS

END
