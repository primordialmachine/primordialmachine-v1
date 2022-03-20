_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; Add two signed 8 bit integers.
; CL = first operand
; DL = second operand
; R8 = pointer to result variable
Ring1_Intrinsic_Add_X64_add_s8 PROC
    ADD cl, dl   ; cl@1 = cl@0 + dl@0 = x + y
    MOV [r8], cl ; [r8]@1 = cl@1
    SETO al      ; al@1 = overflow
    RET          ; RETURN
Ring1_Intrinsic_Add_X64_add_s8 ENDP

_TEXT ENDS

END
