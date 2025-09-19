include "SymphonyInstrFormats.td"

//io指令

def NOP:EmptyInst<IOMode,IOOpNop,(outs),(ins),"nop",[]>;
def IN:DInst<IOMode,IOOpIn, (outs GPR:$DestR), (ins), "in\t$DestR", []>;
def OUTI:IInst<IOMode,IOOpOut, (outs), (ins i16imm:$ArgB), "out\t$ArgB", []>;
def OUTR:RInst<IOMode,IOOpOut, (outs), (ins GPR:$ArgB), "out\t$ArgB", []>;
def CONSOLEI:IInst<IOMode,IOOpConsole, (outs), (ins i16imm:$ArgB), "console\t$ArgB", []>;
def CONSOLER:RInst<IOMode,IOOpConsole, (outs), (ins GPR:$ArgB), "console\t$ArgB", []>;
def TIME0:DInst<IOMode,IOOpTime0, (outs GPR:$DestR), (ins), "time_0\t$DestR", []>;
def TIME1:DInst<IOMode,IOOpTime1, (outs GPR:$DestR), (ins), "time_1\t$DestR", []>;
def TIME2:DInst<IOMode,IOOpTime2, (outs GPR:$DestR), (ins), "time_2\t$DestR", []>;
def TIME3:DInst<IOMode,IOOpTime3, (outs GPR:$DestR), (ins), "time_3\t$DestR", []>;
def COUNTER:DInst<IOMode,IOOpCounter, (outs GPR:$DestR), (ins), "counter\t$DestR", []>;
def KEYBOARD:DInst<IOMode,IOOpCounter, (outs GPR:$DestR), (ins), "keyboard\t$DestR", []>;


// ALU指令

def NANDR:DRRInst<ALUMode,ALUOpNand,(outs GPR:$DestR),(ins GPR:$ArgA, GPR:$ArgB), "nand\t$DestR, $ArgA, $ArgB",[]>;
def NANDI:DRIInst<ALUMode,ALUOpNand,(outs GPR:$DestR),(ins GPR:$ArgA, i16imm:$ArgB), "nand\t$DestR, $ArgA, $ArgB",[]>;

def : Pat<(not (and GPR:$ArgA, GPR:$ArgB)),(NANDR GPR:$ArgA, GPR:$ArgB)>;
def : Pat<(not (and GPR:$ArgA, imm16Pat:$ArgB)),(NANDI GPR:$ArgA, imm16Pat:$ArgB)>;

defm OR:ArithLogicInst<ALUOpOr,"or",or>;

defm AND:ArithLogicInst<ALUOpAnd,"and",and>;

def NORR:DRRInst<ALUMode,ALUOpNor,(outs GPR:$DestR),(ins GPR:$ArgA, GPR:$ArgB), "nor\t$DestR, $ArgA, $ArgB",[]>;
def NORI:DRIInst<ALUMode,ALUOpNor,(outs GPR:$DestR),(ins GPR:$ArgA, i16imm:$ArgB), "nor\t$DestR, $ArgA, $ArgB",[]>;

def : Pat<(not (or GPR:$ArgA, GPR:$ArgB)),(NORR GPR:$ArgA, GPR:$ArgB)>;
def : Pat<(not (or GPR:$ArgA, imm16Pat:$ArgB)),(NORI GPR:$ArgA, imm16Pat:$ArgB)>;

defm ADD:ArithLogicInst<ALUOpAdd,"add",add>;

defm SUB:ArithLogicInst<ALUOpSub,"sub",sub>;

defm XOR:ArithLogicInst<ALUOpXor,"xor",xor>;

defm LSL:ArithLogicInst<ALUOpLsl,"lsl",shl>;

defm LSR:ArithLogicInst<ALUOpLsr,"lsr",srl>;

let DestR = 0b1111, Defs = [FLAGS] in {
def CMPR:RRInst<ALUMode,ALUOpCmp,(outs),(ins GPR:$ArgA, GPR:$ArgB), "cmp\t$ArgA, $ArgB",[]>;
def CMPI:RIInst<ALUMode,ALUOpCmp,(outs),(ins GPR:$ArgA, i16imm:$ArgB), "cmp\t$ArgA, $ArgB",[]>;
}
defm MUL:ArithLogicInst<ALUOpMul,"mul",mul>;

defm UDIV:ArithLogicInst<ALUOpDiv,"udiv",udiv>;

defm ASR:ArithLogicInst<ALUOpAsr,"asr",sra>;

defm UREM:ArithLogicInst<ALUOpRem,"urem",urem>;

//JUM 指令

def jmptarget : Operand<OtherVT>{
    let EncoderMethod = "encodeRelTarget";
}
def reljmptarget : Operand<OtherVT>;


let ArgA = 0b1111, Uses = [FLAGS], isTerminator = 1, isBranch = 1, isBarrier = 1 in{

let isIndirectBranch  = 1 in{
def JMPR:RRInst<JMPMode,CondOpJmp,(outs),(ins GPR:$ArgB),"jmp\t$ArgB",[]>;
def JER:RRInst<JMPMode,CondOpJe,(outs),(ins GPR:$ArgB),"je\t$ArgB",[]>;
def JNER:RRInst<JMPMode,CondOpJne,(outs),(ins GPR:$ArgB),"jne\t$ArgB",[]>;
def JLR:RRInst<JMPMode,CondOpJl,(outs),(ins GPR:$ArgB),"jl\t$ArgB",[]>;
def JGER:RRInst<JMPMode,CondOpJge,(outs),(ins GPR:$ArgB),"jge\t$ArgB",[]>;
def JLER:RRInst<JMPMode,CondOpJle,(outs),(ins GPR:$ArgB),"jle\t$ArgB",[]>;
def JGR:RRInst<JMPMode,CondOpJg,(outs),(ins GPR:$ArgB),"jg\t$ArgB",[]>;
def JBR:RRInst<JMPMode,CondOpJb,(outs),(ins GPR:$ArgB),"jb\t$ArgB",[]>;
def JAER:RRInst<JMPMode,CondOpJae,(outs),(ins GPR:$ArgB),"jae\t$ArgB",[]>;
def JBER:RRInst<JMPMode,CondOpJbe,(outs),(ins GPR:$ArgB),"jbe\t$ArgB",[]>;
def JAR:RRInst<JMPMode,CondOpJa,(outs),(ins GPR:$ArgB),"ja\t$ArgB",[]>;
}
def JMPI:RIInst<JMPMode,CondOpJmp,(outs),(ins jmptarget:$ArgB),"jmp\t$ArgB",[]>;
def JEI:RIInst<JMPMode,CondOpJe,(outs),(ins jmptarget:$ArgB),"je\t$ArgB",[]>;
def JNEI:RIInst<JMPMode,CondOpJne,(outs),(ins jmptarget:$ArgB),"jne\t$ArgB",[]>;
def JLI:RIInst<JMPMode,CondOpJl,(outs),(ins jmptarget:$ArgB),"jl\t$ArgB",[]>;
def JGEI:RIInst<JMPMode,CondOpJge,(outs),(ins jmptarget:$ArgB),"jge\t$ArgB",[]>;
def JLEI:RIInst<JMPMode,CondOpJle,(outs),(ins jmptarget:$ArgB),"jle\t$ArgB",[]>;
def JGI:RIInst<JMPMode,CondOpJg,(outs),(ins jmptarget:$ArgB),"jg\t$ArgB",[]>;
def JBI:RIInst<JMPMode,CondOpJb,(outs),(ins jmptarget:$ArgB),"jb\t$ArgB",[]>;
def JAEI:RIInst<JMPMode,CondOpJae,(outs),(ins jmptarget:$ArgB),"jae\t$ArgB",[]>;
def JBEI:RIInst<JMPMode,CondOpJbe,(outs),(ins jmptarget:$ArgB),"jbe\t$ArgB",[]>;
def JAI:RIInst<JMPMode,CondOpJa,(outs),(ins jmptarget:$ArgB),"ja\t$ArgB",[]>;
}

def : Pat<(brind GPR:$dest),(JMPR GPR:$dest)>;


//MEM指令

//def MemAsmOperand : AsmOperandClass {
//  let Name = "Memri";
//  let ParserMethod = "parseMemOperand";
//}
//栈中不会使用内存立即数，只有全局变量会
def mem_imm : Operand<iPTR>{
    let EncoderMethod = "encodeMemImm";
    //let ParserMatchClass = MemAsmOperand;
}
//def mem_reg : Operand<iPTR>{
//    let ParserMatchClass = MemAsmOperand;
//}

def LOAD8R:DRInst<RAMMode,RAMOpLoad8,(outs GPR:$DestR),(ins GPR:$ArgB),"load_8\t$DestR, [$ArgB]",[]>;
def LOAD8I:DIInst<RAMMode,RAMOpLoad8,(outs GPR:$DestR),(ins mem_imm:$ArgB),"load_8\t$DestR, [$ArgB]",[]>;

def STORE8R:RRInst<RAMMode,RAMOpStore8,(outs),(ins GPR:$ArgB,GPR:$ArgA),"store_8\t[$ArgB], $ArgA",[]>;
def STORE8I:RIInst<RAMMode,RAMOpStore8,(outs),(ins mem_imm:$ArgB,GPR:$ArgA),"store_8\t[$ArgB], $ArgA",[]>;

def LOAD16R:DRInst<RAMMode,RAMOpLoad16,(outs GPR:$DestR),(ins GPR:$ArgB),"load_16\t$DestR, [$ArgB]",[]>;
def LOAD16I:DIInst<RAMMode,RAMOpLoad16,(outs GPR:$DestR),(ins mem_imm:$ArgB),"load_16\t$DestR, [$ArgB]",[]>;

def STORE16R:RRInst<RAMMode,RAMOpStore16,(outs),(ins GPR:$ArgB,GPR:$ArgA),"store_16\t[$ArgB], $ArgA",[]>;
def STORE16I:RIInst<RAMMode,RAMOpStore16,(outs),(ins mem_imm:$ArgB,GPR:$ArgA),"store_16\t[$ArgB], $ArgA",[]>;

//def : Pat<(sextloadi8 imm16Pat:$address),(ANDI (LOAD8I imm16Pat:$address), 0xFF)>;
//def : Pat<(sextloadi8 GPR:$b),(ANDI (LOAD8R GPR:$b), 0xFF)>;
//
def : Pat<(zextloadi8 imm16Pat:$address),(ANDI (LOAD8I imm16Pat:$address), 0xFF)>;
def : Pat<(zextloadi8 GPR:$b),(ANDI (LOAD8R GPR:$b), 0xFF)>;

def : Pat<(extloadi8 imm16Pat:$address),(LOAD8I imm16Pat:$address)>;
def : Pat<(extloadi8 GPR:$b),(LOAD8R GPR:$b)>;

def : Pat<(truncstorei8 GPR:$source,imm16Pat:$address),(STORE8I imm16Pat:$address,GPR:$source)>;
def : Pat<(truncstorei8 GPR:$source,GPR:$address),(STORE8R GPR:$address,GPR:$source)>;

def : Pat<(load imm16Pat:$address),(LOAD16I imm16Pat:$address)>;
def : Pat<(load GPR:$b),(LOAD16R GPR:$b)>;

def : Pat<(store GPR:$source,imm16Pat:$address),(STORE16I imm16Pat:$address,GPR:$source)>;
def : Pat<(store GPR:$source,GPR:$address),(STORE16R GPR:$address,GPR:$source)>;

//def : Pat<(load memPat: $addr), (LOAD memPat:$addr)>;
//def : Pat<(store GPR:$ra, memPat: $addr), (STORE GPR:$ra, memPat: $addr)>;

//cmov系列指令

def SDT_SymphonyCMP:SDTypeProfile<0,2,[
    SDTCisSameAs<0, 1>
]>;
def SymphonyCMP:SDNode<"SymphonyISD::CMP",SDT_SymphonyCMP,[SDNPOutGlue]>;

def : Pat<(SymphonyCMP GPR:$ArgA,GPR:$ArgB),(CMPR GPR:$ArgA,GPR:$ArgB)>;
def : Pat<(SymphonyCMP GPR:$ArgA,imm16Pat:$ArgB),(CMPI GPR:$ArgA,imm16Pat:$ArgB)>;

def SDT_SymphonyCMOV:SDTypeProfile<1,3,[
    SDTCisSameAs<1, 2>, SDTCisSameAs<0, 1>, SDTCisVT<3, i8>
]>;
def SymphonyCMOV:SDNode<"SymphonyISD::CMOV",SDT_SymphonyCMOV,[SDNPInGlue]>;

multiclass CMOV<OpCode op,string asmstr>{
    def R:DRInst<CMOVMode,op,(outs GPR:$DestR),(ins GPR:$ArgB),!strconcat(asmstr, "\t$DestR, $ArgB"),[]>;
    def I:DIInst<CMOVMode,op,(outs GPR:$DestR),(ins i16imm:$ArgB),!strconcat(asmstr, "\t$DestR, $ArgB"),[]>;
}
let ArgA = 0b1111, Uses = [FLAGS] in{
defm MOV:CMOV<CondOpJmp,"mov">;
defm CMOVE:CMOV<CondOpJe,"cmove">;
defm CMOVNE:CMOV<CondOpJne,"cmovne">;
defm CMOVL:CMOV<CondOpJl,"cmovl">;
defm CMOVGE:CMOV<CondOpJge,"cmovge">;
defm CMOVLE:CMOV<CondOpJle,"cmovle">;
defm CMOVG:CMOV<CondOpJg,"cmovg">;
defm CMOVB:CMOV<CondOpJb,"cmovb">;
defm CMOVAE:CMOV<CondOpJae,"cmovae">;
defm CMOVBE:CMOV<CondOpJbe,"cmovbe">;
defm CMOVA:CMOV<CondOpJa,"cmova">;

//def SELECTI:PseudoInst<(outs GPR:$dest),(ins GPR:$a, i16imm:$b, GPR:$true_v, GPR:$false_v, i8imm:$cond),"",[]>;
//def SELECTR:PseudoInst<(outs GPR:$dest),(ins GPR:$a,GPR:$b, GPR:$true_v, GPR:$false_v, i8imm:$cond),"",[]>;
}


def : Pat<(i16 (imm16Pat:$A)),(MOVI imm16Pat:$A)>;

//展开成cmp,mov,cmov，全是寄存器了
def CMOVPseudo : PseudoInst<(outs GPR:$DestR),(ins GPR:$ArgA,GPR:$ArgB,i8imm:$cond),"",[]>;

def : Pat<(SymphonyCMOV GPR:$ArgA,GPR:$ArgB,i8:$cond),(CMOVPseudo GPR:$ArgA,GPR:$ArgB,i8:$cond)>;
def : Pat<(SymphonyCMOV GPR:$ArgA,imm16Pat:$ArgB,i8:$cond),(CMOVPseudo GPR:$ArgA,imm16Pat:$ArgB,i8:$cond)>;
def : Pat<(SymphonyCMOV imm16Pat:$ArgA,GPR:$ArgB,i8:$cond),(CMOVPseudo imm16Pat:$ArgA,GPR:$ArgB,i8:$cond)>;
def : Pat<(SymphonyCMOV imm16Pat:$ArgA,imm16Pat:$ArgB,i8:$cond),(CMOVPseudo imm16Pat:$ArgA,imm16Pat:$ArgB,i8:$cond)>;


//其他部分
def : Pat<(SymphonyWrapper tjumptable:$dest),(MOVI GPR:$dest)>;

//def framidx : Operand<i16>;

//这个伪指令只负责处理单独的frameindex，并且只在内部使用，外界无法使用这个伪指令
let Defs = [R13] in {
//def frameptrget : PseudoInst<(outs GPR:$DestR),(ins memRI:$frameptr),"",[]>;
//def frameptrget : PseudoInst<(outs GPR:$DestR),(ins FrameAddr:$frameptr, i16imm:$offset),"",[]>;
//def frameptrget : PseudoInst<(outs GPR:$dest),(ins GPR:$source, i16imm:$offset),"",[]>;
def frameptrget : PseudoInst<(outs GPR:$dest),(ins GPR:$source),"",[]>;
}

def : Pat<(FrameAddrPat GPR:$Base,imm16ZeroPat:$offset),(ADDI $Base,$offset)>;
def : Pat<(FrameAddrPat GPR:$Base,imm16PosPat:$offset),(ADDI $Base,$offset)>;
def : Pat<(FrameAddrPat GPR:$Base,imm16NegPat:$offset),(SUBI $Base,$offset)>;

let Defs = [R13] in {
def PseudoLoadFr : PseudoInst<(outs GPR:$DestR),(ins FrameAddr:$frameaddr),"",[]>;
def PseudoStoreFr : PseudoInst<(outs),(ins GPR:$from, FrameAddr:$frameaddr),"",[]>;
}

//def : Pat<(load FrameAddrPat:$frameaddr),(PseudoLoadFr FrameAddrPat:$frameaddr)>;
//def : Pat<(store GPR:$from, FrameAddrPat:$frameaddr),(PseudoStoreFr GPR:$from, FrameAddrPat:$frameaddr)>;


//def : Pat<(add FrameAddrPat:$ptr, imm16Pat:$off),(frameptrget FrameAddrPat:$ptr, imm16Pat:$off)>;

//def : Pat<(frameindex:$idx),(imm16Pat:$idx)>;
//def : Pat<(iPTR FrameAddrPat:$frameptr),(frameptrget FrameAddrPat:$frameptr)>;
//def : Pat<(iPTR (FrameAddrPat:$frameptr),(frameptrget FrameAddrPat:$frameptr)>;
//def : Pat<(iPTR frameindex:$fi),(ADDI $fi,0)>;
//def : Pat<(add (iPTR (frameindex:$fi)), imm16Pat:$off),(ADDI $fi, imm16Pat:$off)>;

//def LOAD8REL : PseudoInst<(outs GPR:$DestR),(ins memRI:$reladdr),"",[]>;
//def STORE8REL : PseudoInst<(outs),(ins GPR:$ArgA, memRI:$reladdr),"",[]>;


//def LOAD16REL : PseudoInst<(outs GPR:$DestR),(ins memRI:$reladdr),"",[]>;
//def STORE16REL : PseudoInst<(outs),(ins GPR:$ArgA, memRI:$reladdr),"",[]>;

//def : Pat<(load memRIPat: $addr), (LOAD16REL memRIPat: $addr)>;
//def : Pat<(store GPR:$source, memRIPat: $addr), (STORE16REL GPR:$source, memRIPat: $addr)>;


//其他指令


//函数调用相关

def retglue : SDNode<"SymphonyISD::RET_GLUE",SDTNone,
    [SDNPHasChain,SDNPOptInGlue,SDNPVariadic]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1, Uses = [FLAGS], Defs = [SP] in {
def SymphonyRet : AsmPseudoInst<(outs),(ins),"ret",[(retglue)]>;
}

def SDT_SymphonyCall : SDTypeProfile<0,-1,[SDTCisVT<0,iPTR>]>;
def symphony_call : SDNode<"SymphonyISD::Call",SDT_SymphonyCall,
                    [SDNPHasChain,SDNPOutGlue,
                    SDNPInGlue, SDNPVariadic]>;

def call_symbol : Operand<iPTR>{
    let EncoderMethod = "encodeRelTarget";
}

let isCall = 1, Uses = [FLAGS] in {
def SymphonyCallR : AsmPseudoInst<(outs),(ins GPR:$dest),"call\t$dest",[(symphony_call GPR:$dest)]>;
def SymphonyCallI : AsmPseudoInst<(outs),(ins call_symbol:$dest),"call\t$dest",[(symphony_call tglobaladdr:$dest)]>;
}

//全局地址

//def : Pat<(SymphonyWrapper tglobaladdr:$dest),(MOVI tglobaladdr:$dest)>;

//SLT相关伪指令

//这里的伪指令不会出现在汇编中，会通过展开伪指令的pass展开成游戏支持的指令
//let Defs = [FLAGS] in {

//def SLTRR : PseudoInst<(outs GPR:$DestR),(ins GPR:$ArgA, GPR:$ArgB, ),"",[]>;
//def SLTI : PseudoInst<(outs GPR:$DestR),(ins GPR:$ArgA, i16imm:$ArgB),"",[]>;

//def BEQ : PseudoInst<(outs GPR:$DestR),(ins GPR:$ArgA, GPR:$ArgB, jmptarget:$dest),"",[]>;
//def BNE : PseudoInst<(outs GPR:$DestR),(ins GPR:$ArgA, GPR:$ArgB, jmptarget:$dest),"",[]>;
//def BA : PseudoInst<(outs GPR:$DestR),(ins GPR:$ArgA, GPR:$ArgB, jmptarget:$dest),"",[]>;
//}

//def : Pat<(setgt GPR:$lhs, GPR:$rhs),(SLTR GPR:$rhs, GPR:$lhs)>;
//def : Pat<(setlt GPR:$lhs, GPR:$rhs),(SLTR GPR:$lhs, GPR:$rhs)>;
//def : Pat<(seteq GPR:$lhs, GPR:$rhs),(SLTI (XORR GPR:$lhs, GPR:$rhs), 1)>;
//def : Pat<(setne GPR:$lhs, GPR:$rhs),(SLTR ZR, (XORR GPR:$lhs, GPR:$rhs))>;
//def : Pat<(setge GPR:$lhs, GPR:$rhs),(XORI (SLTR GPR:$lhs, GPR:$rhs), 1)>;
//def : Pat<(setle GPR:$lhs, GPR:$rhs),(XORI (SLTR GPR:$rhs, GPR:$lhs), 1)>;

//def : Pat<(setgt imm16Pat:$lhs, GPR:$rhs),(SLTI GPR:$rhs, imm16Pat:$lhs)>;
//def : Pat<(setlt GPR:$lhs, imm16Pat:$rhs),(SLTI GPR:$lhs, imm16Pat:$rhs)>;
//def : Pat<(seteq GPR:$lhs, imm16Pat:$rhs),(SLTI (XORI GPR:$lhs, imm16Pat:$rhs), 1)>;
//def : Pat<(setne GPR:$lhs, imm16Pat:$rhs),(SLTR ZR, (XORI GPR:$lhs, imm16Pat:$rhs))>;
//def : Pat<(setge GPR:$lhs, imm16Pat:$rhs),(XORI (SLTI GPR:$lhs, imm16Pat:$rhs), 1)>;
//def : Pat<(setle GPR:$lhs, imm16Pat:$rhs),(XORI (SLTI GPR:$rhs, imm16Pat:$lhs), 1)>;

//def : Pat

def SDT_SymphonyBRCC:SDTypeProfile<0,2,[
    SDTCisVT<0, OtherVT>, SDTCisInt<1>
]>;
def SymphonyBRCC:SDNode<"SymphonyISD::BR_CC",SDT_SymphonyBRCC,[SDNPHasChain, SDNPInGlue]>;


def : Pat<(br bb:$dest),(JMPI jmptarget:$dest)>;

def : Pat<(SymphonyBRCC bb:$dest,CondE ),(JEI  jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondNE),(JNEI jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondL ),(JLI  jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondGE),(JGEI jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondLE),(JLEI jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondG ),(JGI  jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondB ),(JBI  jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondAE),(JAEI jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondBE),(JBEI jmptarget:$dest)>;
def : Pat<(SymphonyBRCC bb:$dest,CondA ),(JAI  jmptarget:$dest)>;


//def : Pat<(jumptable:$jtable),(tjumptable:$jtable)>;
//def : Pat<(iPTR jumptable:$jtable),(MOVI tjumptable:$jtable)>;

