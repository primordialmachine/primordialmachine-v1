.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Add_X86_add_s8(int8_t x, int8_t y, int8_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Add_X86_add_s8@12 PROC
    ADD cl, dl   ; cl@1 = cl@0 + dl@0 = x + y
    POP DWORD PTR edx       ; pop return address
    POP DWORD PTR eax       ; eax@0 = &z
    PUSH edx                ; push return address
    MOV BYTE PTR [eax], cl  ; *z@0 = al@2
    SETO al                 ; al@1 = overflow
    RET                     ; RETURN
@Ring1_Intrinsic_Add_X86_add_s8@12 ENDP

_TEXT ENDS

END
