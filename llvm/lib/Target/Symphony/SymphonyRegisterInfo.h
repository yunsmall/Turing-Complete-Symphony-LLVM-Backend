#ifndef SYMPHONYREGISTERINFO_H
#define SYMPHONYREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "SymphonyGenRegisterInfo.inc"

namespace llvm {

class SymphonySubtarget;
class SymphonyRegisterInfo : public SymphonyGenRegisterInfo {
  const SymphonySubtarget& STI;
  public:
  explicit SymphonyRegisterInfo(const SymphonySubtarget& STI);

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;
  BitVector getReservedRegs(const MachineFunction &MF) const override;
  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID) const override;
  bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS) const override;
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // namespace llvm

#endif // SYMPHONYREGISTERINFO_H
