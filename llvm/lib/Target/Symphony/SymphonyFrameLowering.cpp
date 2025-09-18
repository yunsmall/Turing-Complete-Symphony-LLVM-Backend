#include "SymphonyFrameLowering.h"
#include "SymphonySubtarget.h"


#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

uint64_t SymphonyFrameLowering::computeStackSize(MachineFunction &MF) const {
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  uint64_t StackSize = MFI.getStackSize();
  unsigned StackAlign = getStackAlignment();
  if (StackAlign > 0) {
    StackSize = ROUND_UP(StackSize, StackAlign);
  }
  return StackSize;
}

void llvm::SymphonyFrameLowering::emitPrologue(MachineFunction &MF,
                                               MachineBasicBlock &MBB) const {
  const TargetInstrInfo &TII = *STI.getInstrInfo();

  MachineBasicBlock::iterator MBBI = MBB.begin();

  DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();

  uint64_t StackSize = computeStackSize(MF);
  if (StackSize == 0)
    return;
  BuildMI(MBB, MBBI, DL, TII.get(Symphony::SUBI), Symphony::SP)
    .addReg(Symphony::SP)
    .addImm(StackSize)
  .setMIFlag(MachineInstr::FrameSetup);
}
void llvm::SymphonyFrameLowering::emitEpilogue(MachineFunction &MF,
                                               MachineBasicBlock &MBB) const {
  const TargetInstrInfo &TII = *STI.getInstrInfo();

  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();

  DebugLoc DL = MBBI->getDebugLoc();
  uint64_t StackSize = computeStackSize(MF);

  if (StackSize == 0)
    return;

  BuildMI(MBB, MBBI, DL, TII.get(Symphony::ADDI), Symphony::SP)
      .addReg(Symphony::SP)
      .addImm(StackSize)
      .setMIFlag(MachineInstr::FrameDestroy);
}
void SymphonyFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                                 BitVector &SavedRegs,
                                                 RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
}
bool llvm::SymphonyFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  return false;
}