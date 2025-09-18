#ifndef SYMPHONYASMPRINTER_H
#define SYMPHONYASMPRINTER_H

#include "SymphonyTargetMachine.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class SymphonyAsmPrinter : public AsmPrinter {
public:
  SymphonyAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer), ID) {}
  StringRef getPassName() const override { return "Symphony Assembly Printer"; }
  bool runOnMachineFunction(MachineFunction &MF) override;
  void emitInstruction(const MachineInstr *MI) override;
  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                       const char *ExtraCode, raw_ostream &OS) override;
  const MCExpr *lowerConstant(const Constant *CV, const Constant *BaseCV,
                              uint64_t Offset) override;

private:
  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
  bool lowerOperand(const MachineOperand &MO, MCOperand &MCOp);
  void lowerToMCInst(const MachineInstr *MI, MCInst &Out);
  static char ID;
};
} // namespace llvm

#endif // SYMPHONYASMPRINTER_H
