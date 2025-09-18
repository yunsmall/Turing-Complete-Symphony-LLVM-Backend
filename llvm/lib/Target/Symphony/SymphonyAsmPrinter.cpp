#include "SymphonyAsmPrinter.h"

#include "MCTargetDesc/SymphonyMCAsmInfo.h"
#include "MCTargetDesc/SymphonyMCExpr.h"
#include "MCTargetDesc/SymphonyMCTargetDesc.h"

using namespace llvm;

#define PRINT_ALIAS_INSTR
#include "SymphonyGenMCPseudoLowering.inc"

char SymphonyAsmPrinter::ID;
bool SymphonyAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  AsmPrinter::runOnMachineFunction(MF);
  return true;
}
void SymphonyAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // if (MCInst OutInst; lowerPseudoInstExpansion(MI, OutInst)) {
  //   EmitToStreamer(*OutStreamer, OutInst);
  //   return;
  // }
  MCInst TmpInst;
  lowerToMCInst(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}
bool SymphonyAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                                         const char *ExtraCode,
                                         raw_ostream &OS) {
  const MachineOperand &MO = MI->getOperand(OpNo);

  if (MO.isImm()) {
    OS << static_cast<uint16_t>(MO.getImm());
    return false;
  }

  if (!AsmPrinter::PrintAsmOperand(MI, OpNo, ExtraCode, OS))
    return false;

  if (MO.getType() == MachineOperand::MO_GlobalAddress) {
    PrintSymbolOperand(MO, OS); // Print global symbols.
    return false;
  }
  return true;
}
const MCExpr *SymphonyAsmPrinter::lowerConstant(const Constant *CV,
                                                const Constant *BaseCV,
                                                uint64_t Offset) {
  return AsmPrinter::lowerConstant(CV, BaseCV, Offset);
  // return SymphonyMCExpr::create(SymphonyMCAsmInfo::CONSTANT,
  //                               AsmPrinter::lowerConstant(CV, BaseCV,
  //                               Offset), false, OutContext);
}
bool SymphonyAsmPrinter::lowerOperand(const MachineOperand &MO,
                                      MCOperand &MCOp) {
  switch (MO.getType()) {
  default:
    llvm_unreachable("unknown operand type");
  case MachineOperand::MO_Register:
    // Ignore all implicit register operands.
    if (MO.isImplicit())
      return false;
    assert(!MO.getSubReg() && "Subregs should be eliminated!");
    MCOp = MCOperand::createReg(MO.getReg());
    break;
  case MachineOperand::MO_Immediate:
    MCOp = MCOperand::createImm(MO.getImm());
    break;
  case MachineOperand::MO_MachineBasicBlock:
    MCOp = MCOperand::createExpr(
        MCSymbolRefExpr::create(MO.getMBB()->getSymbol(), OutContext));
    break;
  // case MachineOperand::MO_GlobalAddress:
  //   MCOp = GetSymbolRef(MO,
  //                       GetARMGVSymbol(MO.getGlobal(), MO.getTargetFlags()));
  //   break;
  // case MachineOperand::MO_ExternalSymbol:
  //   MCOp = GetSymbolRef(MO,
  //                       GetExternalSymbolSymbol(MO.getSymbolName()));
  //   break;
  // case MachineOperand::MO_JumpTableIndex:
  //   MCOp = GetSymbolRef(MO, GetJTISymbol(MO.getIndex()));
  //   break;
  // case MachineOperand::MO_ConstantPoolIndex:
  //   if (Subtarget->genExecuteOnly())
  //     llvm_unreachable("execute-only should not generate constant pools");
  //   MCOp = GetSymbolRef(MO, GetCPISymbol(MO.getIndex()));
  //   break;
  // case MachineOperand::MO_BlockAddress:
  //   MCOp = GetSymbolRef(MO, GetBlockAddressSymbol(MO.getBlockAddress()));
  //   break;
  // case MachineOperand::MO_FPImmediate: {
  //   APFloat Val = MO.getFPImm()->getValueAPF();
  //   bool ignored;
  //   Val.convert(APFloat::IEEEdouble(), APFloat::rmTowardZero, &ignored);
  //   MCOp =
  //   MCOperand::createDFPImm(bit_cast<uint64_t>(Val.convertToDouble()));
  //   break;
  // }
  case MachineOperand::MO_RegisterMask:
    // Ignore call clobbers.
    return false;
  }
  return true;
}

void SymphonyAsmPrinter::lowerToMCInst(const MachineInstr *MI, MCInst &Out) {
  Out.setOpcode(MI->getOpcode());
  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp;
    switch (MO.getType()) {
    case MachineOperand::MO_Register: {
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;
    }
    case MachineOperand::MO_Immediate: {
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    }
    case MachineOperand::MO_MachineBasicBlock: {
      auto *symbol = MO.getMBB()->getSymbol();
      const MCExpr *Expr = MCSymbolRefExpr::create(symbol, OutContext);
      // Expr = SymphonyMCExpr::create(
      //     SymphonyMCAsmInfo::CONVERT_TO_LEGAL_IDENTIFIER, Expr, OutContext);
      MCOp = MCOperand::createExpr(Expr);
      break;
    }
    case MachineOperand::MO_ExternalSymbol: {
      auto *symbol = GetExternalSymbolSymbol(MO.getSymbolName());
      const MCExpr *Expr = MCSymbolRefExpr::create(symbol, OutContext);
      MCOp = MCOperand::createExpr(Expr);
      break;
    }
    case MachineOperand::MO_GlobalAddress: {
      auto *symbol = getSymbol(MO.getGlobal());
      const auto &expr = MCSymbolRefExpr::create(symbol, 0, OutContext);
      MCOp = MCOperand::createExpr(expr);
      break;
    }
    case MachineOperand::MO_RegisterMask: {
      break;
    }
    default:
      llvm_unreachable("unknown operand type");
    }
    Out.addOperand(MCOp);
  }
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSymphonyAsmPrinter() {
  RegisterAsmPrinter<SymphonyAsmPrinter> X(getTheSymphonyTarget());
}