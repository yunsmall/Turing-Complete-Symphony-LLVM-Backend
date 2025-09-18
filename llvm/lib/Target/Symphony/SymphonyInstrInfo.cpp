#include "SymphonyInstrInfo.h"

#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "Symphony.h"
#include "SymphonySubtarget.h"

#include "llvm/CodeGen/MachineFrameInfo.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "SymphonyGenInstrInfo.inc"

llvm::SymphonyInstrInfo::SymphonyInstrInfo() : SymphonyGenInstrInfo() {}
void SymphonyInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                    MachineBasicBlock::iterator MI,
                                    const DebugLoc &DL, Register DestReg,
                                    Register SrcReg, bool KillSrc,
                                    bool RenamableDest,
                                    bool RenamableSrc) const {
  BuildMI(MBB, MI, DL, get(Symphony::MOVR), DestReg)
      .addReg(SrcReg, getKillRegState(KillSrc));
}
void SymphonyInstrInfo::storeRegToStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register SrcReg,
    bool isKill, int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI, Register VReg,
    MachineInstr::MIFlag Flags) const {
  DebugLoc DL;

  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  // const SymphonySubtarget &STI =
  //     static_cast<const SymphonySubtarget &>(MF.getSubtarget());

  BuildMI(MBB, MI, DL, get(Symphony::frameptrget), Symphony::R13)
      .addFrameIndex(FrameIndex);
  // BuildMI(MBB, MI, DL, get(Symphony::ADDI), Symphony::R13)
  //     .addFrameIndex(FrameIndex)
  //     .addImm(0);

  BuildMI(MBB, MI, DL, get(Symphony::STORE16R))
      .addReg(Symphony::R13, getKillRegState(true))
      .addReg(SrcReg, getKillRegState(isKill));
}
void SymphonyInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                             MachineBasicBlock::iterator MI,
                                             Register DestReg, int FrameIndex,
                                             const TargetRegisterClass *RC,
                                             const TargetRegisterInfo *TRI,
                                             Register VReg,
                                             MachineInstr::MIFlag Flags) const {

  DebugLoc DL;

  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  // const SymphonySubtarget &STI =
  //     static_cast<const SymphonySubtarget &>(MF.getSubtarget());

  BuildMI(MBB, MI, DL, get(Symphony::frameptrget), Symphony::R13)
      .addFrameIndex(FrameIndex);
  // BuildMI(MBB, MI, DL, get(Symphony::ADDI), DestReg)
  //     .addFrameIndex(FrameIndex)
  //     .addImm(0);

  BuildMI(MBB, MI, DL, get(Symphony::LOAD16R))
      .addReg(DestReg)
      .addReg(Symphony::R13, getKillRegState(true));
}