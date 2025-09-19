#include "SymphonyRegisterInfo.h"
#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "Symphony.h"
#include "SymphonySubtarget.h"

#include "llvm/CodeGen/MachineFrameInfo.h"

using namespace llvm;

#define DEBUG_TYPE "symphony-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "SymphonyGenRegisterInfo.inc"

SymphonyRegisterInfo::SymphonyRegisterInfo(const SymphonySubtarget &STI)
    : SymphonyGenRegisterInfo(Symphony::R1), STI(STI) {}
const llvm::MCPhysReg *llvm::SymphonyRegisterInfo::getCalleeSavedRegs(
    const MachineFunction *MF) const {
  return CC_CSR_SaveList;
}
llvm::BitVector
llvm::SymphonyRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  Reserved.set(Symphony::ZR);
  // 专门拿来计算地址偏移
  Reserved.set(Symphony::R13);
  Reserved.set(Symphony::SP);
  Reserved.set(Symphony::FLAGS);
  return Reserved;
}
const uint32_t *
SymphonyRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                           CallingConv::ID id) const {
  return CC_CSR_RegMask;
}
bool llvm::SymphonyRegisterInfo::eliminateFrameIndex(
    MachineBasicBlock::iterator II, int SPAdj, unsigned FIOperandNum,
    RegScavenger *RS) const {

  MachineInstr &MI = *II;
  DebugLoc dl = MI.getDebugLoc();
  MachineBasicBlock &MBB = *MI.getParent();
  LLVM_DEBUG(errs() << MI);

  unsigned OpCode = MI.getOpcode();

  // assert(MI.getOpcode() == Symphony::ADDI);

  unsigned I = 0;
  while (!MI.getOperand(I).isFI()) {
    I++;
    assert(I < MI.getNumOperands());
  }

  const int FI = MI.getOperand(I).getIndex();

  const MachineFunction &MF = *MI.getParent()->getParent();
  const MachineFrameInfo &MFI = MF.getFrameInfo();

  int64_t Offset = MFI.getObjectOffset(FI);
  uint64_t STACKSIZE =
      ROUND_UP(MFI.getStackSize(), STI.getFrameLowering()->getStackAlignment());
  Offset += static_cast<int64_t>(STACKSIZE);

  // Register DestR = MI.getOperand(0).getReg();

  // if (Offset < 0) {
  //   BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::SUBI), DestR)
  //       .addReg(Symphony::SP)
  //       .addImm(-Offset);
  //   MI.eraseFromParent();
  // } else if (MI.getOpcode() == Symphony::ADDI) {
  //   MI.getOperand(I).ChangeToRegister(Symphony::SP, false);
  //   MI.getOperand(I + 1).setImm(Offset);
  // }

  // if (Offset > 0) {
  //   BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::ADDI), DestR)
  //       .addReg(Symphony::SP)
  //       .addImm(Offset);
  // } else if (Offset < 0) {
  //   BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::SUBI), DestR)
  //       .addReg(Symphony::SP)
  //       .addImm(-Offset);
  // } else {
  //   BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::MOVI), DestR)
  //       .addReg(Symphony::SP);
  // }
  if (OpCode == Symphony::frameptrget) {
    Register DestR = MI.getOperand(0).getReg();
    // MI.getOperand(I).isReg()
    if (Offset > 0) {
      BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::ADDI), DestR)
          .addReg(Symphony::SP)
          .addImm(Offset);
    } else if (Offset < 0) {
      BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::SUBI), DestR)
          .addReg(Symphony::SP)
          .addImm(-Offset);
    } else {
      BuildMI(MBB, MI, dl, STI.getInstrInfo()->get(Symphony::MOVR), DestR)
          .addReg(Symphony::SP);
    }
    // 直接删掉这个伪指令
    MI.eraseFromParent();
  } else {
    assert(OpCode == Symphony::PseudoLoadFr ||
           OpCode == Symphony::PseudoStoreFr || OpCode == Symphony::ADDI ||
           OpCode == Symphony::SUBI);
    Offset += MI.getOperand(I + 1).getImm();
    MI.getOperand(I).ChangeToRegister(Symphony::SP, false);
    MI.getOperand(I + 1).ChangeToImmediate(Offset);
  }

  // MI.eraseFromParent();
  return true;
}
llvm::Register
llvm::SymphonyRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Symphony::NoRegister;
}