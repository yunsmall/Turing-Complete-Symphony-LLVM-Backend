
defvar CondALL = 0b1000;
defvar CondE = 0b0001;
defvar CondNE = 0b1001;
defvar CondL = 0b0100;
defvar CondGE = 0b1100;
defvar CondLE = 0b0101;
defvar CondG = 0b1101;
defvar CondB = 0b0010;
defvar CondAE = 0b1010;
defvar CondBE = 0b0011;
defvar CondA = 0b1011;

class Mode<bits<3> v>{
  field bits<3> value=v;
}
def IOMode:Mode<0b000>;
def ALUMode:Mode<0b001>;
def JMPMode:Mode<0b010>;
def RAMMode:Mode<0b011>;
def CMOVMode:Mode<0b100>;

class OpCode<bits<4> v>{
  field bits<4> value=v;
}

def IOOpNop:OpCode<0b0000>;
def IOOpIn:OpCode<0b0001>;
def IOOpOut:OpCode<0b0010>;
def IOOpConsole:OpCode<0b0011>;
def IOOpTime0:OpCode<0b0100>;
def IOOpTime1:OpCode<0b0101>;
def IOOpTime2:OpCode<0b0110>;
def IOOpTime3:OpCode<0b0111>;
def IOOpCounter:OpCode<0b1000>;
def IOOpKeyBoard:OpCode<0b1001>;

def ALUOpNand:OpCode<0b0000>;
def ALUOpOr:OpCode<0b0001>;
def ALUOpAnd:OpCode<0b0010>;
def ALUOpNor:OpCode<0b0011>;
def ALUOpAdd:OpCode<0b0100>;
def ALUOpSub:OpCode<0b0101>;
def ALUOpXor:OpCode<0b0110>;
def ALUOpLsl:OpCode<0b0111>;
def ALUOpLsr:OpCode<0b1000>;
def ALUOpCmp:OpCode<0b1001>;
def ALUOpMul:OpCode<0b1010>;
def ALUOpDiv:OpCode<0b1011>;
def ALUOpAsr:OpCode<0b1100>;
def ALUOpRem:OpCode<0b1101>;

def CondOpJmp:OpCode<CondALL>;
def CondOpJe:OpCode<CondE>;
def CondOpJne:OpCode<CondNE>;
def CondOpJl:OpCode<CondL>;
def CondOpJge:OpCode<CondGE>;
def CondOpJle:OpCode<CondLE>;
def CondOpJg:OpCode<CondG>;
def CondOpJb:OpCode<CondB>;
def CondOpJae:OpCode<CondAE>;
def CondOpJbe:OpCode<CondBE>;
def CondOpJa:OpCode<CondA>;

def RAMOpLoad8:OpCode<0b0000>;
def RAMOpStore8:OpCode<0b0001>;
def RAMOpLoad16:OpCode<0b0010>;
def RAMOpStore16:OpCode<0b0011>;

class SymphonyInst<dag outs, dag ins, string asmstr, list<dag> pattern, Mode mode, OpCode op_code>
  : Instruction {
  let Namespace = "Symphony";

  field bits<32> Inst;

  bits<4> DestR;
  bits<4> ArgA;

  let Inst{31-29}=mode.value;
  let Inst{27-24}=op_code.value;
  let Inst{23-20}=DestR;
  let Inst{19-16}=ArgA;

  let Size = 4;

  let OutOperandList = outs;
  let InOperandList  = ins;

  let AsmString   = asmstr;
  let Pattern     = pattern;
}

class AsmPseudoInst<dag outs, dag ins, string asmstr = "", list<dag> pattern>
    :SymphonyInst<outs,ins,asmstr,pattern,IOMode,IOOpNop>{
    let isPseudo = 1;
}

class PseudoInst<dag outs, dag ins, string asmstr = "", list<dag> pattern>
    :SymphonyInst<outs,ins,asmstr,pattern,IOMode,IOOpNop>{
    let isPseudo = 1;
    let isCodeGenOnly = 1;
}

class SymphonyImmediateInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyInst<outs,ins,asmstr,pattern,mode,op_code>{
  let Inst{28}=1;
  bits<16> ArgB;
  let Inst{15-0}=ArgB;
}

class SymphonyRegInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyInst<outs,ins,asmstr,pattern,mode,op_code>{
  let Inst{28}=0;
  let Inst{15-12}=0;

  bits<4> ArgB;
  let Inst{11-8}=ArgB;

  let Inst{7-0}=0;
}

class EmptyInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyRegInst<mode,op_code,outs,ins,asmstr,pattern>{
  let DestR=0;
  let ArgA=0;
  let ArgB=0;
}

class IInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyImmediateInst<mode,op_code,outs,ins,asmstr,pattern>{
  let DestR=0;
  let ArgA=0;
}

class RInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyRegInst<mode,op_code,outs,ins,asmstr,pattern>{
  let DestR=0;
  let ArgA=0;
}

class DInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyRegInst<mode,op_code,outs,ins,asmstr,pattern>{
  let ArgA=0;
  let ArgB=0;
}

class DIInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyImmediateInst<mode,op_code,outs,ins,asmstr,pattern>{
  let ArgA=0;
}

class DRInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyRegInst<mode,op_code,outs,ins,asmstr,pattern>{
  let ArgA=0;
}


class DRIInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyImmediateInst<mode,op_code,outs,ins,asmstr,pattern>{
}

class DRRInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyRegInst<mode,op_code,outs,ins,asmstr,pattern>{
}

class RIInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyImmediateInst<mode,op_code,outs,ins,asmstr,pattern>{
  let DestR=0;
}

class RRInst<Mode mode,OpCode op_code
          ,dag outs, dag ins, string asmstr, list<dag> pattern>
:SymphonyRegInst<mode,op_code,outs,ins,asmstr,pattern>{
  let DestR=0;
}



def imm16 : Operand<i16>;
def imm16Pat : ImmLeaf<i16 ,[{ return isInt<16>(Imm);}]>;
def imm16PosPat : ImmLeaf<i16 ,[{ return isInt<16>(Imm) && Imm>0;}]>;
def imm16NegPat : ImmLeaf<i16 ,[{ return isInt<16>(Imm) && Imm<0;}]>;
def imm16NotZPat : ImmLeaf<i16 ,[{ return isInt<16>(Imm) && Imm!=0;}]>;
def imm16ZeroPat : ImmLeaf<i16 ,[{ return isInt<16>(Imm) && Imm==0;}]>;

def imm8 : Operand<i8>;
def imm8Pat : ImmLeaf<i8 ,[{ return isInt<8>(Imm);}]>;

def memRI : Operand<iPTR> {
  let MIOperandInfo = (ops GPR, i16imm);
}
def memRIPat : ComplexPattern<iPTR, 2, "SelectRIAddr">;

def FrameAddr : Operand<iPTR> {
  let MIOperandInfo = (ops GPR, i16imm);
}
def FrameAddrPat : ComplexPattern<iPTR, 2, "SelectFrameAddr", [frameindex]>;

def simm16 : Operand<i16> {
  let PrintMethod = "printSImm16Operand";
  let EncoderMethod = "getSImm16OpValue";
  let DecoderMethod = "decodeSImm16Operand";
}


multiclass ArithLogicInst<OpCode op,string inst,SDNode node>{
def I:DRIInst<
      ALUMode,
      op,
      (outs GPR:$DestR),
      (ins GPR:$ArgA,i16imm:$ArgB),
      !strconcat(inst,"\t$DestR, $ArgA, $ArgB"),
      [(set GPR:$DestR, (node GPR:$ArgA, imm16Pat:$ArgB))]
  >;
def R:DRIInst<
      ALUMode,
      op,
      (outs GPR:$DestR),
      (ins GPR:$ArgA,GPR:$ArgB),
      !strconcat(inst,"\t$DestR, $ArgA, $ArgB"),
      [(set GPR:$DestR, (node GPR:$ArgA, GPR:$ArgB))]
  >;
}

//class ArithLogicI<OpCode op,string inst,SDNode node> : DRIInst<
//    ALUMode,
//    op,
//    (outs GPR:$DestR),
//    (ins GPR:$ArgA,i16imm:$ArgB),
//    !strconcat(inst,"\t $DestR, $ArgA, $ArgB"),
//    [(set GPR:$DestR, (node GPR:$ArgA, imm16Pat:$ArgB))]
//>;
//
//class ArithLogicR<OpCode op,string inst,SDNode node> : DRIInst<
//    ALUMode,
//    op,
//    (outs GPR:$DestR),
//    (ins GPR:$ArgA,GPR:$ArgB),
//    !strconcat(inst,"\t $DestR, $ArgA, $ArgB"),
//    [(set GPR:$DestR, (node GPR:$ArgA, GPR:$ArgB))]
//>;

def SDT_SymphonyWrapper : SDTypeProfile<1, 1, [SDTCisSameAs<0, 1>]>;
def SymphonyWrapper : SDNode<"SymphonyISD::WRAPPER", SDT_SymphonyWrapper>;
