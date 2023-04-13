.model flat

_DATA SEGMENT
_DATA ENDS

_TEXT SEGMENT

; char __fastcall Ring1_Intrinsic_Add_X86_add_u64(int64_t x, int64_t y, int64_t *z)
; See README.md for more information.
@Ring1_Intrinsic_Add_X86_add_s64@20 PROC
  MOV eax, DWORD PTR [esp + 4]   ; +4 for the return address                  => x[low]
                                 ; eax@1 = stack[0][low]
  ADD eax, DWORD PTR [esp + 12]  ; +4 for the return address, +8 x            => y[low]
                                 ; eax@2 = eax@1 + stack[1][low]
  MOV edx, DWORD PTR [esp + 8]   ; +4 for the return address, +4 x[low]       => x[high]
                                 ; edx@1 = stack[0][high]
  ADC edx, DWORD PTR [esp + 16]  ; +4 for the return address, +8 x, +4 y[low] => y[high]
                                 ; edx@2 = edx@1 + stack[1][high]
  MOV DWORD PTR [ecx + 0], eax   ; *z[low] = eax@1
  MOV DWORD PTR [ecx + 4], edx   ; *z[high] = edx@1

  SETO al                        ; al@1 = overflow

  POP DWORD PTR ecx ; Pop the return address from the stack into EAX.
  ADD esp, 16       ; Pop the arguments.
  PUSH ecx          ; Push the return address from EAX on the stack.

  RET               ; RETURN
@Ring1_Intrinsic_Add_X86_add_s64@20 ENDP

_TEXT ENDS

END
