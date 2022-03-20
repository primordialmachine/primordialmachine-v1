.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Subtract_X86_subtract_s64(uint64_t x, uint64_t y, uint64_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Subtract_X86_subtract_u64@20 PROC
  MOV eax, DWORD PTR [esp + 4]   ; +4 for the return address                  => x[low]
                                 ; eax@1 = stack[0][low]
  SUB eax, DWORD PTR [esp + 12]  ; +4 for the return address, +8 x            => y[low]
                                 ; eax@2 = eax@1 + stack[1][low]
  MOV edx, DWORD PTR [esp + 8]   ; +4 for the return address, +4 x[low]       => x[high]
                                 ; edx@1 = stack[0][high]
  SBB edx, DWORD PTR [esp + 16]  ; +4 for the return address, +8 x, +4 y[low] => y[high]
                                 ; edx@2 = edx@1 + stack[1][high]
  MOV DWORD PTR [ecx + 0], eax   ; *z[low] = eax@1
  MOV DWORD PTR [ecx + 4], edx   ; *z[high] = edx@1

  SETC al                        ; al@1 = carry

  POP DWORD PTR ecx ; Pop the return address from the stack into ECX.
  ADD esp, 16       ; Pop the arguments.
  PUSH ecx          ; Push the return address from ECX on the stack.

  RET               ; RETURN
@Ring1_Intrinsic_Subtract_X86_subtract_u64@20 ENDP

_TEXT ENDS

END
