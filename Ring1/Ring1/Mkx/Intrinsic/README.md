# Computing the sum and difference signed and unsigned integers
* For the sum and difference of two unsigned integers the usual unsigned binary representation rules apply.
If $x + y$ is greater than `UINTn_MAX`, then it is reduced by modulo `UINTn_MAX + 1`.
For example `UINT8_MAX + 1` is reduced to zero, `UINT8_MAX` is reduced to `1`.
For example `0 - 1` is reduced to `UINT8_MAX` and `0 - 2` is reduced to `UINT8_MAX - 1`.

* For the sum and difference of two signed integers the usual 2 complement binary representation rules apply.

## Implementation details
- For 8 to 32 bit on x86
The functions are using the fastcall calling convention.
The address of z is on the stack followed by the return address. The operands are passed in the registers
of the appropriate size i.e cl/cx/ecx contains the first 8/16/32 integer x, dl/dx/edx contains the second
8/16/32 signed integer y. The @ prefix and the @12 suffix are added by the compiler's name mangling.

- For 64 bit on x86
The functions are using the fastcall calling convention.
The address of z is passed in the ecx register.
The value of x is passed on the stack, followed by the value of y, followed by the return address.
The @ prefix and the @20 suffix are added by the compiler's name mangling.
