_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Add two unsigned 32 bit integers.
; ECX = first operand
; EDX = second operand
; R8 = pointer to result
Ring1_Intrinsic_Add_X64_add_u32 PROC
    ADD ecx, edx  ; ecx@1 = ecx@0 + edx@0 = x + y
    MOV [r8], ecx ; [r8]@1 = ecx@1
    SETC al       ; al@1 = carry
    RET           ; RETURN
Ring1_Intrinsic_Add_X64_add_u32 ENDP

_TEXT ENDS

END
