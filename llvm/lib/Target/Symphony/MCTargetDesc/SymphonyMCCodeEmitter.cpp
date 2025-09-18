//
// Created by 91246 on 25-9-9.
//

#include "SymphonyMCCodeEmitter.h"
#include "MCTargetDesc/SymphonyMCAsmInfo.h"
#include "MCTargetDesc/SymphonyMCTargetDesc.h"

#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/EndianStream.h"

#define DEBUG_TYPE "mccodeemitter"

#define GET_INSTRMAP_INFO
#include "SymphonyGenInstrInfo.inc"

#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCValue.h"
#undef GET_INSTRMAP_INFO

namespace llvm {
class AVRMCExpr;

SymphonyMCCodeEmitter::SymphonyMCCodeEmitter(const MCInstrInfo &MCII,
                                             MCContext &Ctx)
    : MCII(MCII), Ctx(Ctx) {}
void SymphonyMCCodeEmitter::encodeInstruction(
    const MCInst &MI, SmallVectorImpl<char> &CB,
    SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo &STI) const {
  const MCInstrDesc &Desc = MCII.get(MI.getOpcode());

  // Get byte count of instruction
  unsigned Size = Desc.getSize();

  switch (MI.getOpcode()) {
  default:
    break;
  case Symphony::SymphonyRet:
    expandRet(MI, CB, Fixups, STI);
    return;
  case Symphony::SymphonyCallR:
  case Symphony::SymphonyCallI:
    expandCall(MI, CB, Fixups, STI);
    return;
  }

  assert(Size > 0 && "Instruction size cannot be zero");

  uint32_t BinaryOpCode = getBinaryCodeForInstr(MI, Fixups, STI);

  support::endian::write<uint32_t>(CB, BinaryOpCode, llvm::endianness::big);
}
unsigned
SymphonyMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                         SmallVectorImpl<MCFixup> &Fixups,
                                         const MCSubtargetInfo &STI) const {
  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());
  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());

  if (MO.isDFPImm())
    return static_cast<unsigned>(bit_cast<double>(MO.getDFPImm()));

  // MO must be an Expr.
  assert(MO.isExpr());

  return getExprOpValue(MO.getExpr(), Fixups, STI);
}
unsigned
SymphonyMCCodeEmitter::getExprOpValue(const MCExpr *Expr,
                                      SmallVectorImpl<MCFixup> &Fixups,
                                      const MCSubtargetInfo &STI) const {
  MCExpr::ExprKind Kind = Expr->getKind();

  if (Kind == MCExpr::Binary) {
    Expr = static_cast<const MCBinaryExpr *>(Expr)->getLHS();
    Kind = Expr->getKind();
  }
  // llvm_unreachable("Unhandled expression!");

  // if (Kind == MCExpr::Specifier) {
  //   MCValue Res;
  //   Expr->evaluateAsRelocatable(Res, nullptr);
  //   SymphonyMCExpr const *SymphonyExpr = cast<SymphonyMCExpr>(Expr);
  //   int64_t Result;
  //   if (SymphonyExpr->evaluateAsConstant(Result)) {
  //     return Result;
  //   }
  //
  //   MCFixupKind FixupKind =
  //   static_cast<MCFixupKind>(SymphonyExpr->getFixupKind()); addFixup(Fixups,
  //   0, AVRExpr, FixupKind); return 0;
  // }

  assert(Kind == MCExpr::SymbolRef);
  return 0;
}
void SymphonyMCCodeEmitter::expandCall(const MCInst &MI,
                                       SmallVectorImpl<char> &CB,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {
  auto I1 = MCInstBuilder(Symphony::COUNTER).addReg(Symphony::FLAGS);
  auto I1Binary = getBinaryCodeForInstr(I1, Fixups, STI);
  support::endian::write<uint32_t>(CB, I1Binary, llvm::endianness::big);

  auto I2 = MCInstBuilder(Symphony::ADDI)
                .addReg(Symphony::FLAGS)
                .addReg(Symphony::FLAGS)
                .addImm(20);
  auto I2Binary = getBinaryCodeForInstr(I2, Fixups, STI);
  support::endian::write<uint32_t>(CB, I2Binary, llvm::endianness::big);

  auto I3 = MCInstBuilder(Symphony::SUBI)
                .addReg(Symphony::SP)
                .addReg(Symphony::SP)
                .addImm(2);
  auto I3Binary = getBinaryCodeForInstr(I3, Fixups, STI);
  support::endian::write<uint32_t>(CB, I3Binary, llvm::endianness::big);

  auto I4 = MCInstBuilder(Symphony::STORE16R)
                .addReg(Symphony::SP)
                .addReg(Symphony::FLAGS);
  auto I4Binary = getBinaryCodeForInstr(I4, Fixups, STI);
  support::endian::write<uint32_t>(CB, I4Binary, llvm::endianness::big);

  switch (MI.getOpcode()) {
  case Symphony::SymphonyCallI: {
    auto I5 = MCInstBuilder(Symphony::JMPI).addExpr(MI.getOperand(0).getExpr());
    auto I5Binary = getBinaryCodeForInstr(I5, Fixups, STI);
    Fixups.back().setOffset(Fixups.back().getOffset() + 4 * 4);
    support::endian::write<uint32_t>(CB, I5Binary, llvm::endianness::big);
  } break;
  case Symphony::SymphonyCallR: {
    auto I4 = MCInstBuilder(Symphony::JMPR).addReg(MI.getOperand(0).getReg());
    auto I4Binary = getBinaryCodeForInstr(I4, Fixups, STI);
    support::endian::write<uint32_t>(CB, I4Binary, llvm::endianness::big);
  } break;
  default:
    llvm_unreachable_internal("unknown call instruction");
  }
}
void SymphonyMCCodeEmitter::expandRet(const MCInst &MI,
                                      SmallVectorImpl<char> &CB,
                                      SmallVectorImpl<MCFixup> &Fixups,
                                      const MCSubtargetInfo &STI) const {
  auto I1 = MCInstBuilder(Symphony::LOAD16R)
                .addReg(Symphony::FLAGS)
                .addReg(Symphony::SP);
  auto I1Binary = getBinaryCodeForInstr(I1, Fixups, STI);
  support::endian::write<uint32_t>(CB, I1Binary, llvm::endianness::big);

  auto I2 = MCInstBuilder(Symphony::ADDI)
                .addReg(Symphony::SP)
                .addReg(Symphony::SP)
                .addImm(2);
  auto I2Binary = getBinaryCodeForInstr(I2, Fixups, STI);
  support::endian::write<uint32_t>(CB, I2Binary, llvm::endianness::big);

  auto I3 = MCInstBuilder(Symphony::JMPR).addReg(Symphony::FLAGS);
  auto I3Binary = getBinaryCodeForInstr(I3, Fixups, STI);
  support::endian::write<uint32_t>(CB, I3Binary, llvm::endianness::big);
}
unsigned
SymphonyMCCodeEmitter::encodeRelTarget(const MCInst &MI, unsigned OpNo,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);

  if (MO.isExpr()) {
    // int64_t Res;
    // MO.getExpr()->evaluateAsAbsolute()
    if (MI.getOpcode() == Symphony::SymphonyCallI) {
      Fixups.push_back(MCFixup::create(4 * 4 + 2, MO.getExpr(),
                                       MCFixupKind(Symphony::fixup_abs_call)));
    } // jmp系列指令
    else {
      Fixups.push_back(MCFixup::create(2, MO.getExpr(),
                                       MCFixupKind(Symphony::fixup_abs_jmp)));
    }

    return 0;
  }
  assert(MO.isImm());
  auto target = MO.getImm();

  return target;
}
unsigned SymphonyMCCodeEmitter::encodeMemImm(const MCInst &MI, unsigned OpNo,
                                             SmallVectorImpl<MCFixup> &Fixups,
                                             const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);

  if (MO.isExpr()) {
    Fixups.push_back(MCFixup::create(4 * 4 + 2, MO.getExpr(),
                                     MCFixupKind(Symphony::fixup_abs_mem)));
    return 0;
  }
  assert(MO.isImm());
  auto target = MO.getImm();

  return target;
}

#include "SymphonyGenMCCodeEmitter.inc"

MCCodeEmitter *createSymphonyMCCodeEmitter(const MCInstrInfo &MCII,
                                           MCContext &Ctx) {
  return new SymphonyMCCodeEmitter(MCII, Ctx);
}

} // namespace llvm