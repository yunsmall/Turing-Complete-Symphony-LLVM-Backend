#include "SymphonyAsmBackend.h"
#include "SymphonyFixupKinds.h"
#include "SymphonyMCTargetDesc.h"

#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void llvm::SymphonyAsmBackend::adjustFixupValue(const MCFixup &Fixup,
                                                const MCValue &Target,
                                                uint64_t &Value,
                                                MCContext *Ctx) const {}
std::unique_ptr<llvm::MCObjectTargetWriter>
llvm::SymphonyAsmBackend::createObjectTargetWriter() const {
  return createSymphonyELFObjectWriter(TheTriple);
}
void llvm::SymphonyAsmBackend::applyFixup(const MCFragment &F,
                                          const MCFixup &Fixup,
                                          const MCValue &Target,
                                          MutableArrayRef<char> Data,
                                          uint64_t Value, bool IsResolved) {
  if (!IsResolved)
    Asm->getWriter().recordRelocation(F, Fixup, Target, Value);

  MCFixupKind Kind = Fixup.getKind();
  unsigned Offset = Fixup.getOffset();
  unsigned NumBytes = (getFixupKindInfo(Kind).TargetSize + 7) / 8;

  switch (Kind) {
  case Symphony::fixup_abs_jmp:
  case Symphony::fixup_abs_call:
  case Symphony::fixup_abs_mem:
    support::endian::write16be(&Data[Offset], Value);
    break;
  }
}
std::optional<llvm::MCFixupKind>
llvm::SymphonyAsmBackend::getFixupKind(StringRef Name) const {
  return MCAsmBackend::getFixupKind(Name);
}
llvm::MCFixupKindInfo
llvm::SymphonyAsmBackend::getFixupKindInfo(MCFixupKind Kind) const {
  const static MCFixupKindInfo Infos[Symphony::NumTargetFixupKinds] = {
      // This table *must* be in same the order of fixup_* kinds in
      // AVRFixupKinds.h.
      //
      // name                    offset  bits  flags
      {"fixup_abs_jmp", 2, 16, 0},
      {"fixup_abs_call", 4*4+2, 16, 0},
      {"fixup_abs_mem", 2, 16, 0},
  };

  // Fixup kinds from .reloc directive are like R_AVR_NONE. They do not require
  // any extra processing.
  if (mc::isRelocation(Kind))
    return {};

  if (Kind < FirstTargetFixupKind)
    return MCAsmBackend::getFixupKindInfo(Kind);

  assert(unsigned(Kind - FirstTargetFixupKind) <
             Symphony::NumTargetFixupKinds &&
         "Invalid kind!");

  return Infos[Kind - FirstTargetFixupKind];
}
bool llvm::SymphonyAsmBackend::writeNopData(raw_ostream &OS, uint64_t Count,
                                            const MCSubtargetInfo *STI) const {
  assert((Count % 4) == 0 && "NOP instructions must be 4 bytes");
  OS.write_zeros(Count);
  return true;
}

MCAsmBackend *llvm::createSymphonyAsmBackend(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             const MCRegisterInfo &MRI,
                                             const llvm::MCTargetOptions &TO) {
  return new SymphonyAsmBackend(STI.getTargetTriple().getOS());
}