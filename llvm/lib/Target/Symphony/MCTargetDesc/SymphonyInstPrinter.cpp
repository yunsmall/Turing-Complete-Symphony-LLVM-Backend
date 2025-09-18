#include "SymphonyInstPrinter.h"

#include "SymphonyMCAsmInfo.h"
#include "SymphonyRegisterInfo.h"

using namespace llvm;

#define DEBUG_TYPE "symphony asm printer"

#define PRINT_ALIAS_INSTR
#include "SymphonyGenAsmWriter.inc"

void llvm::SymphonyInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) {
  OS << getRegisterName(Reg);
}
void llvm::SymphonyInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                          StringRef Annot,
                                          const MCSubtargetInfo &STI,
                                          raw_ostream &O) {
  if (!printAliasInstr(MI, Address, O))
    printInstruction(MI, Address, O);
  printAnnotation(O, Annot);
}
void llvm::SymphonyInstPrinter::printCustomAliasOperand(const MCInst *MI,
                                                        unsigned OpIdx,
                                                        unsigned PrintMethodIdx,
                                                        raw_ostream &O) {}
void SymphonyInstPrinter::printOperand(const MCInst *MI, int opNum,
                                       raw_ostream &OS) {
  const MCOperand &MO = MI->getOperand(opNum);
  if (MO.isReg()) {
    printRegName(OS, MO.getReg());
    return;
  } else if (MO.isImm()) {
    printImmediate(MI, opNum, OS);
  } else {
    assert(MO.isExpr() && "Unknown operand kind in printOperand");
    MAI.printExpr(OS, *MO.getExpr());
  }
}
void SymphonyInstPrinter::printImmediate(const MCInst *MI, unsigned opNum,
                                         raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(opNum);
  if (MO.isImm())
    //游戏内部的汇编器不支持负数，甚至不支持超过16位的整数
    O << static_cast<uint16_t>(MO.getImm());
  else if (MO.isExpr()) {
    MAI.printExpr(O, *MO.getExpr());
  } else
    llvm_unreachable("Unknown immediate kind");
}