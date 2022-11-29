_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Add two signed 64 bit integers.
; RCX = first operand
; RDX = second operand
; RAX = 1 overflow, 0 no overflow
Ring1_Intrinsic_Add_X64_add_s64 PROC
    ADD rcx, rdx  ; rcx@1 = rcx@0 + rdx@0 = x + y
    MOV [r8], rcx ; [r8]@1 = rcx@1
    SETO al       ; al@1 = overflow
    RET           ; RETURN
Ring1_Intrinsic_Add_X64_add_s64 ENDP

_TEXT ENDS

END
