_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Add two unsigned 16 bit integers.
; CX = first operand
; DX = second operand
; R8 = pointer to result
Ring1_Intrinsic_Add_X64_add_u16 PROC
    ADD cx, dx   ; cx@1 = cx@0 + dx@0 = x + y
    MOV [r8], cx ; [r8]@1 = cx@1
    SETC al      ; al@1 = carry
    RET          ; RETURN
Ring1_Intrinsic_Add_X64_add_u16 ENDP

_TEXT ENDS

END
