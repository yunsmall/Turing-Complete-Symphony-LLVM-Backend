// 定义调用约定
def RetCC_Symphony : CallingConv<[
  // 返回值通过R1传递
  CCIfType<[i16], CCAssignToReg<[R1]>>
]>;

def CC_Symphony : CallingConv<[
  // i8提升为i16
  //CCIfType<[i8], CCPromoteToType<i16>>,

  // 前4个参数通过寄存器R1-R4传递
  CCIfType<[i16], CCAssignToReg<[R1, R2, R3, R4]>>,

  // 其余参数通过栈传递
  CCIfType<[i16], CCAssignToStack<2, 2>>,


]>;

def CC_CSR : CalleeSavedRegs<(add (sequence "R%i", 7, 12))>;
