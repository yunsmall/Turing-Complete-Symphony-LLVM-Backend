# Notes
## Programming Aspects

`int` is 16 bits, pointer is also 16 bits.
It's normal for other value type.

The detail datalayout is as follow:
`E-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n16-S8`

Please try to use `unsigned short` type, because `short` is 16 bits, and it's unsigned, which is bugless.


Other types of addition, subtraction, multiplication and division need to be converted, and some operations need to be converted to `libcall` which is a function call, but those `libcall` are not yet implemented.

Can use struct or class

Don't write too complex functions; bugs are easy to create. Function parameters please try to use all integers, Pointers, references, do not directly pass structure.

Floating-point support is not yet available, again due to soft floating-point so `libcall` is not yet implemented

## Compilation Aspects

It's not support to compile to elf file directly using clang, please compile them step by step.
For example:
```powershell
clang.exe --target=symphony -c /path/to/standard_lib\lib\io.s -o io.o
clang.exe --target=symphony -c /path/to/standard_lib\lib\start.s -o start.o
clang.exe --target=symphony -O3 -I /path/to/standard_lib/include -c main.c -o main.o
ld.lld.exe -T .\link.lds .\io.o .\start.o .\main.o -o test.elf
llvm-objcopy.exe -O binary .\test.elf .\test.bin
```
Then load `test.bin` at the RAM in your game.

To see the instruction selection details you can add the `--debug` flag to clang to see if it was an instruction selection issue.

If there are instruction selection bugs, changing the program to `unsigned short` will reduce most of the problems.

Turn on O3 as much as possible, so that the optimization is done at the IR level


## Hardware

cmov series instructions are added, and some more operations are added to the ALU, so the circuit needs to be modified.

You can see the encoding in the `llvm/asm_description.ini` file.

The cmov instruction selects the values of ArgA and ArgB according to the results of the previous cmp. ArgA can only be a register, and ArgB can be an immediate number or a register. Choose ArgA if the condition holds, ArgB otherwise

To select two immediate numbers, use the following command, using let r1 be one of two immediate numbers 1 or 2 as an example
```asm
mov r2,2
cmp r2,3

mov r1,1
cmove r1,r1,2
```
2 compares to 3, it's obviously not equal.
`cmove r1,r1,2` means if equal than r1=r1, else r1=2


The mov instruction is modified to unconditional mov in cmov


## The Author's Words

If there are bugs in other parts, you can issue issues. This project is pure practice, because there are too many things in llvm, some parts are likely to have bugs.

If you have some compiler experience and are interested in Turing Complete, you are welcome to help improve it.
