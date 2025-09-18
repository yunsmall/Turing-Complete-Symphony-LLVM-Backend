#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "Symphony.h"
#include "SymphonyISelLowering.h"
#include "SymphonyInstrInfo.h"
#include "SymphonyTargetMachine.h"

#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

using namespace llvm;

#define Symphony_EXPAND_PSEUDO_NAME "Symphony pseudo instruction expansion pass"

namespace {

class SymphonyExpandPseudo : public MachineFunctionPass {
public:
  static char ID;

  SymphonyExpandPseudo() : MachineFunctionPass(ID) {}

  bool runOnMachineFunction(MachineFunction &MF) override;

  StringRef getPassName() const override { return Symphony_EXPAND_PSEUDO_NAME; }

private:
  typedef MachineBasicBlock Block;
  typedef Block::iterator BlockIt;

  const SymphonyRegisterInfo *TRI;
  const TargetInstrInfo *TII;

  bool expandMBB(Block &MBB);
  bool expandMI(Block &MBB, BlockIt MBBI);
  template <unsigned OP> bool expand(Block &MBB, BlockIt MBBI);

  MachineInstrBuilder buildMI(Block &MBB, BlockIt MBBI, unsigned Opcode) {
    return BuildMI(MBB, MBBI, MBBI->getDebugLoc(), TII->get(Opcode));
  }

  MachineInstrBuilder buildMI(Block &MBB, BlockIt MBBI, unsigned Opcode,
                              Register DstReg) {
    return BuildMI(MBB, MBBI, MBBI->getDebugLoc(), TII->get(Opcode), DstReg);
  }

  MachineRegisterInfo &getRegInfo(Block &MBB) {
    return MBB.getParent()->getRegInfo();
  }

  unsigned getCMOVInst(bool isReg, unsigned Cond);
};

unsigned SymphonyExpandPseudo::getCMOVInst(bool isReg, unsigned Cond) {
  if (isReg) {
    switch (Cond) {
    case SymphonyCC::CondE: {
      return Symphony::CMOVER;
    }
    case SymphonyCC::CondNE: {
      return Symphony::CMOVNER;
    }
    case SymphonyCC::CondL: {
      return Symphony::CMOVLR;
    }
    case SymphonyCC::CondGE: {
      return Symphony::CMOVGER;
    }
    case SymphonyCC::CondLE: {
      return Symphony::CMOVLER;
    }
    case SymphonyCC::CondG: {
      return Symphony::CMOVGR;
    }
    case SymphonyCC::CondB: {
      return Symphony::CMOVBR;
    }
    case SymphonyCC::CondAE: {
      return Symphony::CMOVAER;
    }
    case SymphonyCC::CondBE: {
      return Symphony::CMOVBER;
    }
    case SymphonyCC::CondA: {
      return Symphony::CMOVAR;
    }
    }
  } else {
    switch (Cond) {
    case SymphonyCC::CondE: {
      return Symphony::CMOVEI;
    }
    case SymphonyCC::CondNE: {
      return Symphony::CMOVNEI;
    }
    case SymphonyCC::CondL: {
      return Symphony::CMOVLI;
    }
    case SymphonyCC::CondGE: {
      return Symphony::CMOVGEI;
    }
    case SymphonyCC::CondLE: {
      return Symphony::CMOVLEI;
    }
    case SymphonyCC::CondG: {
      return Symphony::CMOVGI;
    }
    case SymphonyCC::CondB: {
      return Symphony::CMOVBI;
    }
    case SymphonyCC::CondAE: {
      return Symphony::CMOVAEI;
    }
    case SymphonyCC::CondBE: {
      return Symphony::CMOVBEI;
    }
    case SymphonyCC::CondA: {
      return Symphony::CMOVAI;
    }
    }
  }
}
char SymphonyExpandPseudo::ID = 0;

bool SymphonyExpandPseudo::expandMBB(MachineBasicBlock &MBB) {
  bool Modified = false;

  BlockIt MBBI = MBB.begin(), E = MBB.end();
  while (MBBI != E) {
    BlockIt NMBBI = std::next(MBBI);
    Modified |= expandMI(MBB, MBBI);
    MBBI = NMBBI;
  }

  return Modified;
}

bool SymphonyExpandPseudo::runOnMachineFunction(MachineFunction &MF) {
  bool Modified = false;

  const SymphonySubtarget &STI = MF.getSubtarget<SymphonySubtarget>();
  TRI = STI.getRegisterInfo();
  TII = STI.getInstrInfo();

  for (Block &MBB : MF) {
    bool ContinueExpanding = true;
    unsigned ExpandCount = 0;

    // Continue expanding the block until all pseudos are expanded.
    do {
      assert(ExpandCount < 10 && "pseudo expand limit reached");
      (void)ExpandCount;

      bool BlockModified = expandMBB(MBB);
      Modified |= BlockModified;
      ExpandCount++;

      ContinueExpanding = BlockModified;
    } while (ContinueExpanding);
  }

  return Modified;
}

// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SymphonyRet>(Block &MBB,
//                                                          BlockIt MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//
//   buildMI(MBB, MBBI, Symphony::LOAD16I,
//   Symphony::FLAGS).addReg(Symphony::SP); buildMI(MBB, MBBI, Symphony::ADDI,
//   Symphony::SP)
//       .addReg(Symphony::SP)
//       .addImm(2);
//   buildMI(MBB, MBBI, Symphony::JMPR).addReg(Symphony::FLAGS);
//
//   MI.eraseFromParent();
//   return true;
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SymphonyCallI>(Block &MBB,
//                                                            BlockIt MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//
//   buildMI(MBB, MBBI, Symphony::COUNTER, Symphony::FLAGS);
//   buildMI(MBB, MBBI, Symphony::ADDI, Symphony::FLAGS)
//       .addReg(Symphony::FLAGS)
//       .addImm(20);
//   buildMI(MBB, MBBI, Symphony::SUBI, Symphony::SP)
//       .addReg(Symphony::SP)
//       .addImm(2);
//   buildMI(MBB, MBBI, Symphony::STORE16R)
//       .addReg(Symphony::SP)
//       .addReg(Symphony::FLAGS);
//   buildMI(MBB, MBBI, Symphony::JMPI)
//       .addGlobalAddress(MI.getOperand(0).getGlobal());
//
//   MI.eraseFromParent();
//   return true;
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SymphonyCallR>(Block &MBB,
//                                                            BlockIt MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//
//   buildMI(MBB, MBBI, Symphony::COUNTER, Symphony::FLAGS);
//   buildMI(MBB, MBBI, Symphony::ADDI, Symphony::FLAGS)
//       .addReg(Symphony::FLAGS)
//       .addImm(20);
//   buildMI(MBB, MBBI, Symphony::SUBI, Symphony::SP)
//       .addReg(Symphony::SP)
//       .addImm(2);
//   buildMI(MBB, MBBI, Symphony::STORE16R)
//       .addReg(Symphony::SP)
//       .addReg(Symphony::FLAGS);
//   buildMI(MBB, MBBI, Symphony::JMPI).addReg(MI.getOperand(0).getReg());
//
//   MI.eraseFromParent();
//   return true;
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SLTI>(Block &MBB, BlockIt MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//   MachineOperand &DestR = MI.getOperand(0);
//   MachineOperand &ArgA = MI.getOperand(1);
//   MachineOperand &ArgB = MI.getOperand(2);
//
//   buildMI(MBB, MBBI, Symphony::CMPI)
//       .addReg(ArgA.getReg())
//       .addImm(ArgB.getImm());
//   buildMI(MBB, MBBI, Symphony::CONDR, DestR.getReg())
//       .addReg(Symphony::FLAGS)
//       .addImm(SymphonyCC::CondL);
//
//   MI.eraseFromParent();
//   return true;
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SLTR>(Block &MBB, BlockIt MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//   MachineOperand &DestR = MI.getOperand(0);
//   MachineOperand &ArgA = MI.getOperand(1);
//   MachineOperand &ArgB = MI.getOperand(2);
//
//   buildMI(MBB, MBBI, Symphony::CMPR)
//       .addReg(ArgA.getReg())
//       .addReg(ArgB.getReg());
//   buildMI(MBB, MBBI, Symphony::CONDR, DestR.getReg())
//       .addReg(Symphony::FLAGS)
//       .addImm(SymphonyCC::CondL);
//
//   MI.eraseFromParent();
//   return true;
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SLTUI>(Block &MBB, BlockIt MBBI)
// {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//   MachineOperand &DestR = MI.getOperand(0);
//   MachineOperand &ArgA = MI.getOperand(1);
//   MachineOperand &ArgB = MI.getOperand(2);
//
//   buildMI(MBB, MBBI, Symphony::CMPR)
//       .addReg(ArgA.getReg())
//       .addImm(ArgB.getImm());
//   buildMI(MBB, MBBI, Symphony::CONDR, DestR.getReg())
//       .addReg(Symphony::FLAGS)
//       .addImm(SymphonyCC::CondB);
//
//   MI.eraseFromParent();
//   return true;
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SLTUR>(Block &MBB, BlockIt MBBI)
// {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//   MachineOperand &DestR = MI.getOperand(0);
//   MachineOperand &ArgA = MI.getOperand(1);
//   MachineOperand &ArgB = MI.getOperand(2);
//
//   buildMI(MBB, MBBI, Symphony::CMPR)
//       .addReg(ArgA.getReg())
//       .addReg(ArgB.getReg());
//   buildMI(MBB, MBBI, Symphony::CONDR, DestR.getReg())
//       .addReg(Symphony::FLAGS)
//       .addImm(SymphonyCC::CondL);
//
//   MI.eraseFromParent();
//   return true;
// }

// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SELECTR>(Block &MBB, BlockIt
// MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//   MachineOperand &DestR = MI.getOperand(0);
//   MachineOperand &ArgA = MI.getOperand(1);
//   MachineOperand &ArgB = MI.getOperand(2);
//   MachineOperand &TrueV = MI.getOperand(3);
//   MachineOperand &FalseV = MI.getOperand(4);
//   MachineOperand &Cond = MI.getOperand(5);
//
//   buildMI(MBB, MBBI, Symphony::CMPR)
//        .addReg(ArgA.getReg())
//        .addReg(ArgB.getReg());
//   buildMI(MBB,MBBI,Symphony::CMO)
// }
//
// template <>
// bool SymphonyExpandPseudo::expand<Symphony::SELECTI>(Block &MBB, BlockIt
// MBBI) {
//   // MachineFunction &MF = *MBB.getParent();
//   MachineInstr &MI = *MBBI;
//   // MachineRegisterInfo &MRI = MF.getRegInfo();
//   MachineOperand &DestR = MI.getOperand(0);
//   MachineOperand &ArgA = MI.getOperand(1);
//   MachineOperand &ArgB = MI.getOperand(2);
// }

template <>
bool SymphonyExpandPseudo::expand<Symphony::CMOVPseudo>(Block &MBB,
                                                        BlockIt MBBI) {
  // MachineFunction &MF = *MBB.getParent();
  MachineInstr &MI = *MBBI;
  // MachineRegisterInfo &MRI = MF.getRegInfo();
  MachineOperand &DestR = MI.getOperand(0);
  MachineOperand &ArgA = MI.getOperand(1);
  MachineOperand &ArgB = MI.getOperand(2);
  MachineOperand &Cond = MI.getOperand(3);

  // cmp a,b
  // mov d,b
  // cmovxx a
  // 如果满足条件d=a，否则b
  // 如果b是寄存器相应改变

  bool ArgAisReg = ArgA.isReg();
  bool ArgBisReg = ArgB.isReg();

  unsigned CMOV = getCMOVInst(ArgAisReg, Cond.getImm());

  if (ArgBisReg) {
    buildMI(MBB, MBBI, Symphony::MOVR, DestR.getReg()).addReg(ArgB.getReg());
  } else {
    buildMI(MBB, MBBI, Symphony::MOVI, DestR.getReg()).addImm(ArgB.getImm());
  }
  if (ArgAisReg) {
    buildMI(MBB, MBBI, CMOV, DestR.getReg()).addReg(ArgA.getReg());
  } else {
    buildMI(MBB, MBBI, CMOV, DestR.getReg()).addImm(ArgA.getImm());
  }

  MI.eraseFromParent();
  return true;
}

template <>
bool SymphonyExpandPseudo::expand<Symphony::PseudoLoadFr>(Block &MBB,
                                                          BlockIt MBBI) {
  // MachineFunction &MF = *MBB.getParent();
  MachineInstr &MI = *MBBI;
  // MachineRegisterInfo &MRI = MF.getRegInfo();
  Register DestR = MI.getOperand(0).getReg();
  Register Base = MI.getOperand(1).getReg();
  int64_t Offset = MI.getOperand(2).getImm();

  if (Offset < 0) {
    buildMI(MBB, MBBI, Symphony::SUBI, DestR).addReg(Base).addImm(-Offset);
  } else if (Offset > 0) {
    buildMI(MBB, MBBI, Symphony::ADDI, DestR).addReg(Base).addImm(Offset);
  } else {
    buildMI(MBB, MBBI, Symphony::MOVI, DestR).addReg(Base);
  }
  buildMI(MBB, MBBI, Symphony::LOAD16R, DestR).addReg(DestR);

  MI.eraseFromParent();
  return true;
}

template <>
bool SymphonyExpandPseudo::expand<Symphony::PseudoStoreFr>(Block &MBB,
                                                           BlockIt MBBI) {
  // MachineFunction &MF = *MBB.getParent();
  MachineInstr &MI = *MBBI;
  // MachineRegisterInfo &MRI = MF.getRegInfo();
  Register FromReg = MI.getOperand(0).getReg();
  Register Base = MI.getOperand(1).getReg();
  int64_t Offset = MI.getOperand(2).getImm();

  if (Offset < 0) {
    buildMI(MBB, MBBI, Symphony::SUBI, Symphony::R13)
        .addReg(Base)
        .addImm(-Offset);
  } else if (Offset > 0) {
    buildMI(MBB, MBBI, Symphony::ADDI, Symphony::R13)
        .addReg(Base)
        .addImm(Offset);
  } else {
    buildMI(MBB, MBBI, Symphony::MOVI, Symphony::R13).addReg(Base);
  }
  buildMI(MBB, MBBI, Symphony::STORE16R, Symphony::R13).addReg(FromReg);

  MI.eraseFromParent();
  return true;
}

bool SymphonyExpandPseudo::expandMI(Block &MBB, BlockIt MBBI) {
  MachineInstr &MI = *MBBI;
  int Opcode = MBBI->getOpcode();

#define EXPAND(Op)                                                             \
  case Op:                                                                     \
    return expand<Op>(MBB, MI)

  switch (Opcode) {
    // EXPAND(Symphony::SLTI);
    // EXPAND(Symphony::SLTR);
    // EXPAND(Symphony::SLTUI);
    // EXPAND(Symphony::SLTUR);
    // EXPAND(Symphony::SymphonyRet);
    // EXPAND(Symphony::SymphonyCallI);
    // EXPAND(Symphony::SymphonyCallR);
    EXPAND(Symphony::CMOVPseudo);
    EXPAND(Symphony::PseudoLoadFr);
    EXPAND(Symphony::PseudoStoreFr);
  }
#undef EXPAND
  return false;
}

} // end of anonymous namespace

INITIALIZE_PASS(SymphonyExpandPseudo, "symphony-expand-pseudo",
                Symphony_EXPAND_PSEUDO_NAME, false, false)

FunctionPass *llvm::createSymphonyExpandPseudoPass() {
  return new SymphonyExpandPseudo();
}
