
#include "MCTargetDesc/SymphonyFixupKinds.h"
#include "SymphonyMCAsmInfo.h"
#include "SymphonyMCTargetDesc.h"

#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {

class SymphonyELFObjectWriter : public MCELFObjectTargetWriter {
public:
  explicit SymphonyELFObjectWriter(uint8_t OSABI);

  ~SymphonyELFObjectWriter() override = default;

  [[nodiscard]] unsigned getRelocType(const MCFixup &, const MCValue &,
                                      bool IsPCRel) const override;
};

SymphonyELFObjectWriter::SymphonyELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(false, OSABI, ELF::EM_SYMPHONY, true) {}
unsigned SymphonyELFObjectWriter::getRelocType(const MCFixup &Fixup,
                                               const MCValue &Target,
                                               bool IsPCRel) const {
  auto Spec = Target.getSpecifier();
  switch ((unsigned)Fixup.getKind()) {
  case Symphony::fixup_abs_jmp:
    return ELF::R_SYMPHONY_ABS;
  case Symphony::fixup_abs_mem:
    return ELF::R_SYMPHONY_ABS;
  // case FK_Data_2:
  //   switch (Spec) {
  //   default:
  //     llvm_unreachable("Unsupported Modifier");
  //   }
  default:
    llvm_unreachable("invalid fixup kind!");
  }
}
std::unique_ptr<MCObjectTargetWriter>
createSymphonyELFObjectWriter(const Triple &TT) {
  uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(TT.getOS());
  return std::make_unique<SymphonyELFObjectWriter>(OSABI);
}

} // namespace llvm
