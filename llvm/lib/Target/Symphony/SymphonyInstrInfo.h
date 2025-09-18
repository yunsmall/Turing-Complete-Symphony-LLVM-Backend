#ifndef SYMPHONYINSTRINFO_H
#define SYMPHONYINSTRINFO_H


#include "llvm/CodeGen/TargetInstrInfo.h"


#define GET_INSTRINFO_HEADER
#include "SymphonyGenInstrInfo.inc"

namespace llvm{
class SymphonyInstrInfo:public SymphonyGenInstrInfo {
public:
  explicit SymphonyInstrInfo();
  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                   const DebugLoc &DL, Register DestReg, Register SrcReg,
                   bool KillSrc, bool RenamableDest,
                   bool RenamableSrc) const override;
  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, Register SrcReg,
                           bool isKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI, Register VReg,
                           MachineInstr::MIFlag Flags) const override;
  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MI, Register DestReg,
                            int FrameIndex, const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI, Register VReg,
                            MachineInstr::MIFlag Flags) const override;
};

}

#endif //SYMPHONYINSTRINFO_H
