#include "SymphonyISelLowering.h"
#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "SymphonySubtarget.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"

using namespace llvm;

#include "SymphonyGenCallingConv.inc"

llvm::SymphonyTargetLowering::SymphonyTargetLowering(
    const TargetMachine &TM, const SymphonySubtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {
  addRegisterClass(MVT::i16, &Symphony::GPRRegClass);

  setOperationAction(ISD::GlobalAddress, MVT::i16, Custom);
  // 常量
  setOperationAction(ISD::Constant, MVT::i32, Expand);
  setOperationAction(ISD::Constant, MVT::i64, Expand);
  // 分支
  setOperationAction(ISD::SELECT, MVT::i16, Expand);
  setOperationAction(ISD::SELECT_CC, MVT::i16, Custom);
  setOperationAction(ISD::SETCC, MVT::i16, Expand);
  setOperationAction(ISD::BR_CC, MVT::i16, Custom);
  setOperationAction(ISD::BRCOND, MVT::Other, Expand);

  setOperationAction(ISD::JumpTable, MVT::i16, Custom);
  setOperationAction(ISD::BR_JT, MVT::Other, Expand);
  // setOperationAction(ISD::BR_JT, MVT::Other, Custom);

  // 浮点
  //  setOperationAction(ISD::FADD,MVT::f)

  // 内存操作
  for (MVT VT : MVT::integer_valuetypes()) {
    for (auto N : {ISD::EXTLOAD, ISD::SEXTLOAD, ISD::ZEXTLOAD}) {
      setLoadExtAction(N, VT, MVT::i1, Promote);
      // setLoadExtAction(N, VT, MVT::i16, Expand);
    }
    setLoadExtAction(ISD::SEXTLOAD, VT, MVT::i8, Expand);
    // for (auto N : {ISD::EXTLOAD, ISD::SEXTLOAD, ISD::ZEXTLOAD}) {
    //   setLoadExtAction(N, VT, MVT::i1, Promote);
    //   setLoadExtAction(N, VT, MVT::i8, Promote);
    //   setLoadExtAction(N, VT, MVT::i16, Expand);
    // }
  }
  // setOperationAction(ISD::ZEXTLOAD, MVT::i16, Expand);
  // setOperationAction(ISD::SEXTLOAD, MVT::i16, Expand);

  // 算术
  setOperationAction(ISD::MUL, MVT::i8, Promote);
  setOperationAction(ISD::MUL, MVT::i32, Expand);
  setOperationAction(ISD::MUL, MVT::i64, Expand);
  setOperationAction(ISD::MUL, MVT::i128, Expand);

  setOperationAction(ISD::SDIV, MVT::i8, Expand);
  setOperationAction(ISD::SDIV, MVT::i16, Expand);
  setOperationAction(ISD::SDIV, MVT::i32, Expand);
  setOperationAction(ISD::SDIV, MVT::i64, Expand);

  setOperationAction(ISD::SDIVREM, MVT::i8, Expand);
  setOperationAction(ISD::SDIVREM, MVT::i16, Expand);
  setOperationAction(ISD::SDIVREM, MVT::i32, Expand);
  setOperationAction(ISD::SDIVREM, MVT::i64, Expand);

  setOperationAction(ISD::SREM, MVT::i8, Expand);
  setOperationAction(ISD::SREM, MVT::i16, Expand);
  setOperationAction(ISD::SREM, MVT::i32, Expand);
  setOperationAction(ISD::SREM, MVT::i64, Expand);

  setOperationAction(ISD::UDIV, MVT::i8, Promote);
  setOperationAction(ISD::UDIV, MVT::i32, Expand);
  setOperationAction(ISD::UDIV, MVT::i64, Expand);

  // setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i16, Expand);
  // setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i32, Expand);
  // setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i64, Expand);

  setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i8, Expand);
  setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i16, Expand);
  setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i32, Expand);
  setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::i64, Expand);
  // for (MVT VT : MVT::integer_valuetypes()) {
  //   setOperationAction(ISD::SIGN_EXTEND, VT, Custom);
  // }
  // setOperationAction(ISD::EXTLOAD, MVT::i16, Custom);

  // setOperationAction(ISD::SRL, MVT::i32, Custom);
  // setOperationAction(ISD::SRL, MVT::i64, Custom);
  // setOperationAction(ISD::SHL, MVT::i32, Custom);
  // setOperationAction(ISD::SHL, MVT::i64, Expand);

  setOperationAction(ISD::SRL_PARTS, MVT::i16, Custom);
  // setOperationAction(ISD::SRL_PARTS, MVT::i16, Expand);
  setOperationAction(ISD::SRL_PARTS, MVT::i32, Expand);
  setOperationAction(ISD::SRL_PARTS, MVT::i64, Expand);
  setOperationAction(ISD::SRA_PARTS, MVT::i16, Custom);
  // setOperationAction(ISD::SRA_PARTS, MVT::i16, Expand);
  setOperationAction(ISD::SRA_PARTS, MVT::i32, Expand);
  setOperationAction(ISD::SRA_PARTS, MVT::i64, Expand);

  setOperationAction(ISD::SHL_PARTS, MVT::i16, Custom);
  // setOperationAction(ISD::SHL_PARTS, MVT::i16, Expand);
  setOperationAction(ISD::SRL_PARTS, MVT::i32, Expand);
  setOperationAction(ISD::SRL_PARTS, MVT::i64, Expand);

  for (MVT VT : MVT::integer_valuetypes()) {
    setOperationAction(ISD::MULHS, VT, Expand);
    setOperationAction(ISD::MULHU, VT, Expand);
  }

  for (MVT VT : MVT::integer_valuetypes()) {
    setOperationAction(ISD::SMUL_LOHI, VT, Expand);
    setOperationAction(ISD::UMUL_LOHI, VT, Expand);
  }

  computeRegisterProperties(STI.getRegisterInfo());
}

llvm::SDValue llvm::SymphonyTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  MachineFunction &MF = DAG.getMachineFunction();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, MF, ArgLocs, *DAG.getContext());
  CCInfo.AnalyzeFormalArguments(Ins, CC_Symphony);

  SDValue ArgValue;
  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    if (VA.isRegLoc()) {
      MVT RegVT = VA.getLocVT();
      Register Reg = MF.addLiveIn(VA.getLocReg(), &Symphony::GPRRegClass);
      ArgValue = DAG.getCopyFromReg(Chain, DL, Reg, RegVT);
      InVals.push_back(ArgValue);
    } else {
      assert(VA.isMemLoc());

      MVT ValVT = VA.getValVT();

      // call指令会压栈PC，跳过PC的内存区域
      int Offset = VA.getLocMemOffset() + 2;
      int FI = MFI.CreateFixedObject(ValVT.getSizeInBits() / 8, Offset, true);

      SDValue FIN = DAG.getFrameIndex(FI, getPointerTy(DAG.getDataLayout()));
      SDValue Val = DAG.getLoad(
          ValVT, DL, Chain, FIN,
          MachinePointerInfo::getFixedStack(DAG.getMachineFunction(), FI));
      InVals.push_back(Val);
    }
  }

  return Chain;
}
SDValue
SymphonyTargetLowering::LowerCall(CallLoweringInfo &CLI,
                                  SmallVectorImpl<SDValue> &InVals) const {
  SelectionDAG &DAG = CLI.DAG;
  SDLoc &DL = CLI.DL;
  SmallVectorImpl<ISD::OutputArg> &Outs = CLI.Outs;
  SmallVectorImpl<SDValue> &OutVals = CLI.OutVals;
  SmallVectorImpl<ISD::InputArg> &Ins = CLI.Ins;
  SDValue Chain = CLI.Chain;
  SDValue Callee = CLI.Callee;
  CallingConv::ID CallConv = CLI.CallConv;
  bool &IsTailCall = CLI.IsTailCall;
  bool IsVarArg = CLI.IsVarArg;

  MachineFunction &MF = DAG.getMachineFunction();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, MF, ArgLocs, *DAG.getContext());
  CCInfo.AnalyzeCallOperands(Outs, CC_Symphony);

  SmallVector<std::pair<unsigned, SDValue>> RegsPairs;
  SDValue StackPtr;

  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    if (VA.isRegLoc()) {
      RegsPairs.push_back(std::make_pair(VA.getLocReg(), OutVals[i]));
    } else {
      assert(VA.isMemLoc());
      if (!StackPtr.getNode()) {
        StackPtr = DAG.getCopyFromReg(Chain, DL, Symphony::SP,
                                      getPointerTy(DAG.getDataLayout()));
      }
      unsigned LocMemOffset = VA.getLocMemOffset();
      SDValue PtrOff = DAG.getIntPtrConstant(LocMemOffset, DL);
      PtrOff = DAG.getNode(ISD::ADD, DL, getPointerTy(DAG.getDataLayout()),
                           StackPtr, PtrOff);
      /// store val -> reg + offset
      Chain = DAG.getStore(Chain, DL, OutVals[i], PtrOff,
                           MachinePointerInfo::getStack(MF, LocMemOffset));
    }
  }

  if (auto *N = dyn_cast<GlobalAddressSDNode>(Callee)) {
    Callee = DAG.getTargetGlobalAddress(N->getGlobal(), DL,
                                        getPointerTy(DAG.getDataLayout()));
  } else if (auto *N = dyn_cast<ExternalSymbolSDNode>(Callee)) {
    Callee = DAG.getTargetExternalSymbol(N->getSymbol(),
                                         getPointerTy(DAG.getDataLayout()));
  }

  SmallVector<SDValue, 4> Ops(1, Chain);
  Ops.push_back(Callee);
  SDValue Glue;

  for (unsigned i = 0, e = RegsPairs.size(); i != e; ++i) {
    auto &[reg, val] = RegsPairs[i];
    Chain = DAG.getCopyToReg(Chain, DL, RegsPairs[i].first, RegsPairs[i].second,
                             Glue);
    Glue = Chain.getValue(1);
    Ops.push_back(DAG.getRegister(reg, val.getValueType()));
  }

  const TargetRegisterInfo *TRI = Subtarget.getRegisterInfo();
  const uint32_t *Mask =
      TRI->getCallPreservedMask(DAG.getMachineFunction(), CallConv);
  Ops.push_back(DAG.getRegisterMask(Mask));
  if (Glue.getNode()) {
    Ops.push_back(Glue);
  }

  SDVTList NodeTys = DAG.getVTList(MVT::Other, MVT::Glue);
  Chain = DAG.getNode(SymphonyISD::Call, DL, NodeTys, Ops);
  {
    SDValue Glue = Chain.getValue(1);
    SmallVector<CCValAssign, 2> RVLos;
    CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLos,
                   *DAG.getContext());
    CCInfo.AnalyzeCallResult(Ins, RetCC_Symphony);
    for (unsigned i = 0, e = RVLos.size(); i < e; ++i) {
      CCValAssign &VA = RVLos[i];
      EVT vt = RVLos[i].getLocVT();
      assert(VA.isRegLoc());
      unsigned RVReg = VA.getLocReg();
      SDValue Val = DAG.getCopyFromReg(Chain, DL, RVReg, vt, Glue);
      Chain = Val.getValue(1);
      Glue = Val.getValue(2);
      InVals.push_back(Val);
    }
  }
  return Chain;
}
SDValue SymphonyTargetLowering::LowerOperation(SDValue Op,
                                               SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::GlobalAddress:
    return LowerGlobalAddress(Op, DAG);
  // case ISD::Constant:
  //   return LowerConstant(Op, DAG);
  case ISD::FrameIndex:
    return LowerFrameIndex(Op, DAG);
  // case ISD::SETCC:
  //   return LowerSETCC(Op, DAG);
  case ISD::BR_CC:
    return LowerBR_CC(Op, DAG);
  case ISD::SELECT_CC:
    return LowerSELECT_CC(Op, DAG);
  // case ISD::SIGN_EXTEND:
  //   return LowerSIGN_EXTEND(Op, DAG);
  case ISD::SHL_PARTS:
    return LowerShiftLeftParts(Op, DAG);
  case ISD::SRL_PARTS:
  case ISD::SRA_PARTS:
    return LowerShiftRightParts(Op, DAG);
  case ISD::JumpTable:
    return LowerJumpTable(Op, DAG);
  // case ISD::BR_JT:
  // return LowerBR_JT(Op, DAG);
  default:
    llvm_unreachable_internal("unknown operation");
  }
  return SDValue();
}
SDValue SymphonyTargetLowering::LowerFrameIndex(SDValue Op,
                                                SelectionDAG &DAG) const {
  SDLoc DL(Op);
  auto *N = cast<FrameIndexSDNode>(Op);

  SDValue TFI = DAG.getTargetFrameIndex(N->getIndex(), Op.getValueType());

  return TFI;
}
SDValue SymphonyTargetLowering::LowerGlobalAddress(SDValue Op,
                                                   SelectionDAG &DAG) const {
  EVT VT = Op.getValueType();
  GlobalAddressSDNode *N = dyn_cast<GlobalAddressSDNode>(Op);
  SDLoc DL(N);

  uint64_t Offset = N->getOffset();

  SDValue TGA = DAG.getTargetGlobalAddress(N->getGlobal(), DL, VT);

  // SDValue Wrapper = DAG.getNode(SymphonyISD::WRAPPER, DL, VT, TGA, TGA);

  if (Offset == 0) {
    return TGA;
    // return Wrapper;
  }
  // return DAG.getNode(ISD::ADD, DL, VT, Wrapper,
  //                    DAG.getConstant(Offset, DL, VT));
  return DAG.getNode(ISD::ADD, DL, VT, TGA, DAG.getConstant(Offset, DL, VT));
}
SDValue SymphonyTargetLowering::LowerConstant(SDValue Op,
                                              SelectionDAG &DAG) const {
  SDLoc DL(Op);
  EVT VT = Op.getValueType();

  int32_t Imm = dyn_cast<ConstantSDNode>(Op)->getSExtValue();

  if (isInt<16>(Imm)) {
    SDValue SDImm = DAG.getTargetConstant(Imm, DL, VT);
    DAG.getMachineNode(Symphony::MOVI, DL, VT, SDImm);
  }

  return SDValue();
}
SDValue SymphonyTargetLowering::LowerShiftLeftParts(SDValue Op,
                                                    SelectionDAG &DAG) const {
  assert(Op.getNumOperands() == 3 && "Not a double-shift!");
  EVT VT = Op.getValueType();
  unsigned VTBits = VT.getSizeInBits();
  SDLoc dl(Op);
  SDValue ShOpLo = Op.getOperand(0);
  SDValue ShOpHi = Op.getOperand(1);
  SDValue ShAmt = Op.getOperand(2);
  SDValue ARMcc;

  assert(Op.getOpcode() == ISD::SHL_PARTS);
  SDValue RevShAmt = DAG.getNode(ISD::SUB, dl, MVT::i16,
                                 DAG.getConstant(VTBits, dl, MVT::i16), ShAmt);
  SDValue Tmp1 = DAG.getNode(ISD::SRL, dl, VT, ShOpLo, RevShAmt);
  SDValue Tmp2 = DAG.getNode(ISD::SHL, dl, VT, ShOpHi, ShAmt);
  SDValue HiSmallShift = DAG.getNode(ISD::OR, dl, VT, Tmp1, Tmp2);

  SDValue ExtraShAmt = DAG.getNode(ISD::SUB, dl, MVT::i16, ShAmt,
                                   DAG.getConstant(VTBits, dl, MVT::i16));
  SDValue HiBigShift = DAG.getNode(ISD::SHL, dl, VT, ShOpLo, ExtraShAmt);

  uint16_t CMpHICC = CCToSymphonyCC(ISD::SETGE);
  SDValue CmpHi = DAG.getNode(SymphonyISD::CMP, dl, MVT::Glue, ExtraShAmt,
                              DAG.getConstant(0, dl, MVT::i16));
  SDValue Glue = CmpHi.getValue(0);

  SDValue Hi = DAG.getNode(SymphonyISD::CMOV, dl, VT, HiSmallShift, HiBigShift,
                           DAG.getTargetConstant(CMpHICC, dl, MVT::i8), Glue);
  uint16_t CMpLoCC = CCToSymphonyCC(ISD::SETGE);

  SDValue CmpLo = DAG.getNode(SymphonyISD::CMP, dl, MVT::Glue, ExtraShAmt,
                              DAG.getConstant(0, dl, MVT::i16));
  Glue = CmpLo.getValue(0);
  SDValue LoSmallShift = DAG.getNode(ISD::SHL, dl, VT, ShOpLo, ShAmt);
  SDValue Lo = DAG.getNode(SymphonyISD::CMOV, dl, VT, LoSmallShift,
                           DAG.getTargetConstant(0, dl, VT),
                           DAG.getTargetConstant(CMpLoCC, dl, MVT::i8), Glue);

  SDValue Ops[2] = {Lo, Hi};
  return DAG.getMergeValues(Ops, dl);
}

SDValue SymphonyTargetLowering::LowerShiftRightParts(SDValue Op,
                                                     SelectionDAG &DAG) const {
  assert(Op.getNumOperands() == 3 && "Not a double-shift!");
  EVT VT = Op.getValueType();
  unsigned VTBits = VT.getSizeInBits();
  SDLoc dl(Op);
  SDValue ShOpLo = Op.getOperand(0);
  SDValue ShOpHi = Op.getOperand(1);
  SDValue ShAmt = Op.getOperand(2);
  SDValue ARMcc;
  unsigned Opc = (Op.getOpcode() == ISD::SRA_PARTS) ? ISD::SRA : ISD::SRL;

  assert(Op.getOpcode() == ISD::SRA_PARTS || Op.getOpcode() == ISD::SRL_PARTS);

  SDValue RevShAmt = DAG.getNode(ISD::SUB, dl, MVT::i16,
                                 DAG.getConstant(VTBits, dl, MVT::i16), ShAmt);
  SDValue Tmp1 = DAG.getNode(ISD::SRL, dl, VT, ShOpLo, ShAmt);
  SDValue ExtraShAmt = DAG.getNode(ISD::SUB, dl, MVT::i16, ShAmt,
                                   DAG.getConstant(VTBits, dl, MVT::i16));
  SDValue Tmp2 = DAG.getNode(ISD::SHL, dl, VT, ShOpHi, RevShAmt);
  SDValue LoSmallShift = DAG.getNode(ISD::OR, dl, VT, Tmp1, Tmp2);
  SDValue LoBigShift = DAG.getNode(Opc, dl, VT, ShOpHi, ExtraShAmt);

  uint16_t CMpLoCC = CCToSymphonyCC(ISD::SETGE);

  SDValue CmpLo = DAG.getNode(SymphonyISD::CMP, dl, MVT::Glue, ExtraShAmt,
                              DAG.getConstant(0, dl, MVT::i16));
  SDValue Glue = CmpLo.getValue(0);

  SDValue Lo = DAG.getNode(SymphonyISD::CMOV, dl, VT, LoSmallShift, LoBigShift,
                           DAG.getTargetConstant(CMpLoCC, dl, MVT::i8), Glue);

  SDValue HiSmallShift = DAG.getNode(Opc, dl, VT, ShOpHi, ShAmt);
  SDValue HiBigShift = Opc == ISD::SRA
                           ? DAG.getNode(Opc, dl, VT, ShOpHi,
                                         DAG.getConstant(VTBits - 1, dl, VT))
                           : DAG.getConstant(0, dl, VT);

  uint16_t CMpHiCC = CCToSymphonyCC(ISD::SETGE);
  SDValue CmpHi = DAG.getNode(SymphonyISD::CMP, dl, MVT::Glue, ExtraShAmt,
                              DAG.getConstant(0, dl, MVT::i16));
  Glue = CmpHi.getValue(0);
  SDValue Hi = DAG.getNode(SymphonyISD::CMOV, dl, VT, HiSmallShift, HiBigShift,
                           DAG.getTargetConstant(CMpHiCC, dl, MVT::i8), Glue);
  SDValue Ops[2] = {Lo, Hi};
  return DAG.getMergeValues(Ops, dl);
}
SDValue SymphonyTargetLowering::LowerJumpTable(SDValue Op,
                                               SelectionDAG &DAG) const {
  JumpTableSDNode *JT = cast<JumpTableSDNode>(Op);
  EVT VT = Op.getValueType();
  SDLoc dl(Op);
  // return DAG.getTargetJumpTable(JT->getIndex(), VT);
  // return DAG.getCopyToReg(VT,dl,)
  return DAG.getNode(SymphonyISD::WRAPPER, dl, VT,
                     DAG.getTargetJumpTable(JT->getIndex(), VT));
}
// SDValue SymphonyTargetLowering::LowerBR_JT(SDValue Op,
//                                            SelectionDAG &DAG) const {
//   SDValue Chain = Op.getOperand(0);
//   SDValue Table = Op.getOperand(1);    // 跳转表节点，包含跳转表索引
//   SDValue Index = Op.getOperand(2);    // 这是计算后的偏移量，不是原始case值
//   SDLoc dl(Op);
//
//   // Index 已经是映射到跳转表内的偏移量
//   // 例如，如果最小case值是10，那么case值10对应偏移量0，20对应1，等等
//
//   // 确保索引是16位
//   Index = DAG.getNode(ISD::ZERO_EXTEND, dl, MVT::i16, Index);
//
//   // 计算跳转表项地址
//   EVT PTy = getPointerTy(DAG.getDataLayout());
//   SDValue EntryOffset = DAG.getNode(ISD::MUL, dl, PTy, Index,
//   DAG.getConstant(2, dl, PTy)); SDValue EntryAddr = DAG.getNode(ISD::ADD, dl,
//   PTy, Table, EntryOffset);
//
//   // 加载目标地址
//   SDValue TargetAddr = DAG.getLoad(PTy, dl, Chain, EntryAddr,
//   MachinePointerInfo());
//
//   // 创建间接跳转
//   return DAG.getNode(ISD::BRIND, dl, MVT::Other, Chain, TargetAddr);
// }

bool SymphonyTargetLowering::allowsMisalignedMemoryAccesses(
    EVT evt, unsigned AddrSpace, Align Alignment,
    MachineMemOperand::Flags Flags, unsigned *p) const {
  if (p) {
    *p = 1;
  }
  return true;
}
bool SymphonyTargetLowering::allowsMisalignedMemoryAccesses(
    LLT llt, unsigned AddrSpace, Align Alignment,
    MachineMemOperand::Flags Flags, unsigned *p) const {
  if (p) {
    *p = 1;
  }
  return true;
}
SDValue SymphonyTargetLowering::LowerSELECT_CC(SDValue Op,
                                               SelectionDAG &DAG) const {
  SDValue LHS = Op.getOperand(0);
  SDValue RHS = Op.getOperand(1);
  SDValue TrueV = Op.getOperand(2);
  SDValue FalseV = Op.getOperand(3);
  ISD::CondCode CC = cast<CondCodeSDNode>(Op.getOperand(4))->get();
  SDLoc DL(Op);

  SDValue CMP = DAG.getNode(SymphonyISD::CMP, DL, MVT::Glue, LHS, RHS);
  SDValue Glue = CMP.getValue(0);

  uint16_t TargetCC = CCToSymphonyCC(CC);

  SDValue CondCode = DAG.getTargetConstant(TargetCC, DL, MVT::i8);

  return DAG.getNode(SymphonyISD::CMOV, DL, MVT::i16, TrueV, FalseV, CondCode,
                     Glue);
}
// SDValue SymphonyTargetLowering::LowerSIGN_EXTEND(SDValue Op,
//                                                  SelectionDAG &DAG) const {
// SDNode *N = Op.getNode();
// SDLoc DL(N);
//
// EVT IN_VT = Op.getValue(1).getValueType();
// EVT VT = Op.getValueType();
//
// uint64_t OriginBitSize = IN_VT.getSizeInBits();
// uint64_t TargetBitSize = VT.getSizeInBits();
//
// DAG.getNode(ISD::SRL, DL, IN_VT,
// DAG.getConstant(OriginBitSize-1,DL,MVT::i8));
//
//     DAG.getNode();
//
// return DAG.getNode(SymphonyISD::WRAPPER, DL, VT, TGA, TGA);
// }
// SDValue SymphonyTargetLowering::LowerSETCC(SDValue Op,
//                                            SelectionDAG &DAG) const {
//   SDLoc DL(Op);
//   SDValue CMP = DAG.getNode(SymphonyISD::CMP, DL, MVT::Glue,
//   Op.getOperand(0),
//                             Op.getOperand(1));
//   SDValue Glue = CMP.getValue(0);
//   // assert(Glue.get)
//
//   ISD::CondCode CC = cast<CondCodeSDNode>(Op.getOperand(2))->get();
//
//   uint16_t TargetCC = CCToSymphonyCC(CC);
//
//   SDValue CondCode = DAG.getConstant(TargetCC, DL, MVT::i16);
//
//   return DAG.getNode(SymphonyISD::SETCC, DL, MVT::i16, CondCode, Glue);
// }

SDValue SymphonyTargetLowering::LowerBR_CC(SDValue Op,
                                           SelectionDAG &DAG) const {
  SDValue Chain = Op.getOperand(0);
  ISD::CondCode CC = cast<CondCodeSDNode>(Op.getOperand(1))->get();
  SDValue LHS = Op.getOperand(2);
  SDValue RHS = Op.getOperand(3);
  SDValue Dest = Op.getOperand(4);
  SDLoc DL(Op);

  SDValue CMP = DAG.getNode(SymphonyISD::CMP, DL, MVT::Glue, LHS, RHS);
  SDValue Glue = CMP.getValue(0);
  uint16_t TargetCC = CCToSymphonyCC(CC);
  SDValue CondCode = DAG.getConstant(TargetCC, DL, MVT::i16);

  return DAG.getNode(SymphonyISD::BR_CC, DL, MVT::Other, Chain, Dest, CondCode,
                     Glue);
}

SDValue SymphonyTargetLowering::LowerBR_COND(SDValue Op,
                                             SelectionDAG &DAG) const {
  SDValue Chain = Op.getOperand(0);
  ISD::CondCode CC = cast<CondCodeSDNode>(Op.getOperand(1))->get();
  SDValue LHS = Op.getOperand(2);
  SDValue RHS = Op.getOperand(3);
  SDValue Dest = Op.getOperand(4);
  SDLoc DL(Op);

  SDValue CMP = DAG.getNode(SymphonyISD::CMP, DL, MVT::Glue, LHS, RHS);
  SDValue Glue = CMP.getValue(0);
  uint16_t TargetCC = CCToSymphonyCC(CC);
  SDValue CondCode = DAG.getConstant(TargetCC, DL, MVT::i16);

  return DAG.getNode(SymphonyISD::BR_CC, DL, MVT::Other, Chain, Dest, CondCode,
                     Glue);
}

llvm::SDValue llvm::SymphonyTargetLowering::LowerReturn(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs,
    const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
    SelectionDAG &DAG) const {
  SmallVector<CCValAssign, 16> RVLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());
  CCInfo.AnalyzeReturn(Outs, RetCC_Symphony);

  SDValue Glue;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  for (unsigned i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), OutVals[i], Glue);
    Glue = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  RetOps[0] = Chain;

  if (Glue.getNode()) {
    RetOps.push_back(Glue);
  }
  return DAG.getNode(SymphonyISD::RET_GLUE, DL, MVT::Other, RetOps);
}

const char *SymphonyTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case SymphonyISD::RET_GLUE:
    return "SymphonyISD::RET_GLUE";
  case SymphonyISD::Call:
    return "SymphonyISD::Call";
  case SymphonyISD::WRAPPER:
    return "SymphonyISD::WRAPPER";
  case SymphonyISD::CMP:
    return "SymphonyISD::CMP";
  case SymphonyISD::SELECT_CC:
    return "SymphonyISD::SELECT_CC";
  case SymphonyISD::BR_CC:
    return "SymphonyISD::BR_CC";
  case SymphonyISD::CMOV:
    return "SymphonyISD::CMOV";
  default:
    return nullptr;
  }
}
uint16_t SymphonyTargetLowering::CCToSymphonyCC(uint16_t CC) {
  switch (CC) {
  case ISD::SETEQ:
  case ISD::SETUEQ:
    return SymphonyCC::CondE;
  case ISD::SETGT:
  case ISD::SETUGT:
    return SymphonyCC::CondG;
  case ISD::SETGE:
  case ISD::SETUGE:
    return SymphonyCC::CondGE;
  case ISD::SETLT:
  case ISD::SETULT:
    return SymphonyCC::CondL;
  case ISD::SETLE:
  case ISD::SETULE:
    return SymphonyCC::CondLE;
  case ISD::SETNE:
  case ISD::SETUNE:
    return SymphonyCC::CondNE;
  default:
    llvm_unreachable_internal("unknown CC");
  }
}