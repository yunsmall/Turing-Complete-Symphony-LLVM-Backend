#ifndef SYMPHONYMCCODEEMITTER_H
#define SYMPHONYMCCODEEMITTER_H

#include "SymphonyFixupKinds.h"

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/Support/DataTypes.h"

#define GET_INSTRINFO_OPERAND_TYPES_ENUM
#include "SymphonyGenInstrInfo.inc"

namespace llvm {

class MCContext;
class MCExpr;
class MCFixup;
class MCInst;
class MCInstrInfo;
class MCOperand;
class MCSubtargetInfo;
class raw_ostream;

class SymphonyMCCodeEmitter : public MCCodeEmitter {
public:
  SymphonyMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
  unsigned getExprOpValue(const MCExpr *Expr, SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const;
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;
  void expandCall(const MCInst &MI, SmallVectorImpl<char> &CB,
                  SmallVectorImpl<MCFixup> &Fixups,
                  const MCSubtargetInfo &STI) const;
  void expandRet(const MCInst &MI, SmallVectorImpl<char> &CB,
                 SmallVectorImpl<MCFixup> &Fixups,
                 const MCSubtargetInfo &STI) const;
  unsigned encodeRelTarget(const MCInst &MI, unsigned OpNo,
                           SmallVectorImpl<MCFixup> &Fixups,
                           const MCSubtargetInfo &STI) const;
  unsigned encodeMemImm(const MCInst &MI, unsigned OpNo,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
private:
  const MCInstrInfo &MCII;
  MCContext &Ctx;
};

} // namespace llvm

#endif // SYMPHONYMCCODEEMITTER_H
