# 注意事项
## 编程方面
`int`是16位的，指针是16位的。
其他类型位数正常

具体数据布局如下
`E-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n16-S8`

尽量使用`unsigned short`类型，因为`short`是16位的，而且是无符号数，不容易出bug。

其他类型的加减乘除需要进行转换，部分运算需要转换成`libcall`即函数调用，但`libcall`暂时未实现。

可以使用结构体等。

不要写太复杂的函数，很容易出bug。函数传参请尽量全用整数、指针、引用，不要直接传结构体。

暂不支持浮点，同样是由于是软浮点因此暂时没实现`libcall`

## 编译方面

暂时不支持clang直接编译到elf
请一步步编译
如：
```powershell
clang.exe --target=symphony -c /path/to/standard_lib\lib\io.s -o io.o
clang.exe --target=symphony -c /path/to/standard_lib\lib\start.s -o start.o
clang.exe --target=symphony -O3 -I /path/to/standard_lib/include -c main.c -o main.o
ld.lld.exe -T .\link.lds .\io.o .\start.o .\main.o -o test.elf
llvm-objcopy.exe -O binary .\test.elf .\test.bin
```
游戏中直接加载`test.bin`即可

使用clang时请添加参数
`-fno-builtin -fno-jump-tables`，jump table暂时未实现，若生成了包含jumptable的IR会指令选择失败。

想查看指令选择细节可以给clang添加`--debug`参数，可通过此参数查看是否是指令选择的问题。

如果有指令选择的bug就将程序往`unsigned short`类型上修改，能减少绝大多数问题。

尽量开O3，让优化都在IR层面做掉


## 硬件

添加了cmov系列指令，ALU中也多添加了部分运算，需要修改电路。

具体怎么改可以看`llvm/asm_description.ini`文件中的编码。

cmov系列指令根据之前cmp的结果选择ArgA和ArgB的值，ArgA只能为寄存器，ArgB可以是立即数或者寄存器。如果条件成立选择ArgA，否则ArgB

想选择两个立即数可采用如下指令，以r1选择为两个立即数1或者2做示例
```asm
mov r2,2
cmp r2,3

mov r1,1
cmove r1,r1,2
```
2和3比较，自然是不相等的
`cmove r1,r1,2`的效果是相等则r1=r1，否则r1=2



mov指令修改成了cmov中的无条件mov


## 作者的话

其他部分若有bug可以发issue，本项目纯纯练手的，由于llvm东西太多了，有些部分很可能有bug。

欢迎有编译器开发经验且对Turing Complete这款游戏感兴趣的大佬帮忙改进。