#ifndef SYMPHONYISELLOWERING_H
#define SYMPHONYISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
class SymphonySubtarget;
namespace SymphonyISD {
enum NodeType : unsigned {
  FIERST_NUMBER = ISD::BUILTIN_OP_END,
  RET_GLUE,
  Call,
  WRAPPER,
  CMP,
  SETCC,
  SELECT_CC,
  BR_CC,
  CMOV
};
}

namespace SymphonyCC {
enum CC : unsigned {
  CondALL = 0b1000,
  CondE = 0b0001,
  CondNE = 0b1001,
  CondL = 0b0100,
  CondGE = 0b1100,
  CondLE = 0b0101,
  CondG = 0b1101,
  CondB = 0b0010,
  CondAE = 0b1010,
  CondBE = 0b0011,
  CondA = 0b1011,
};
}
class SymphonyTargetLowering : public TargetLowering {
  const SymphonySubtarget &Subtarget;

public:
  explicit SymphonyTargetLowering(const TargetMachine &TM,
                                  const SymphonySubtarget &STI);

  const SymphonySubtarget &getSubtarget() const { return Subtarget; }
  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;
  SDValue LowerCall(CallLoweringInfo &,
                    SmallVectorImpl<SDValue> &) const override;
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  SDValue LowerFrameIndex(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerConstant(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerShiftLeftParts(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerShiftRightParts(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerJumpTable(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerBR_JT(SDValue Op, SelectionDAG &DAG) const;
  // SDValue LowerSIGN_EXTEND(SDValue Op, SelectionDAG &DAG) const;
  bool allowsMisalignedMemoryAccesses(EVT, unsigned AddrSpace, Align Alignment,
                                      MachineMemOperand::Flags Flags,
                                      unsigned *) const override;
  bool allowsMisalignedMemoryAccesses(LLT, unsigned AddrSpace, Align Alignment,
                                      MachineMemOperand::Flags Flags,
                                      unsigned *) const override;
  SDValue LowerSELECT_CC(SDValue Op, SelectionDAG &DAG) const;
  // SDValue LowerSETCC(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerBR_CC(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerBR_COND(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Ins,
                      const SmallVectorImpl<SDValue> &, const SDLoc &DL,
                      SelectionDAG &DAG) const override;
  const char *getTargetNodeName(unsigned Opcode) const override;

private:
  static uint16_t CCToSymphonyCC(uint16_t CC);
};
} // namespace llvm
#endif // SYMPHONYISELLOWERING_H
