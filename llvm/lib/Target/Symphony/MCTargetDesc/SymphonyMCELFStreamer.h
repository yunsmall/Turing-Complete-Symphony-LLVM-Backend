#ifndef SYMPHONYMCELFSTREAMER_H
#define SYMPHONYMCELFSTREAMER_H

#include "SymphonyMCTargetDesc.h"

#include "MCTargetDesc/SymphonyMCAsmInfo.h"
#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"

namespace llvm {
class SymphonyMCELFStreamer : public MCELFStreamer {
  std::unique_ptr<MCInstrInfo> MCII;

public:
  SymphonyMCELFStreamer(MCContext &Context, std::unique_ptr<MCAsmBackend> TAB,
                        std::unique_ptr<MCObjectWriter> OW,
                        std::unique_ptr<MCCodeEmitter> Emitter)
      : MCELFStreamer(Context, std::move(TAB), std::move(OW),
                      std::move(Emitter)),
        MCII(createSymphonyMCInstrInfo()) {}
  SymphonyMCELFStreamer(MCContext &Context, std::unique_ptr<MCAsmBackend> TAB,
                 std::unique_ptr<MCObjectWriter> OW,
                 std::unique_ptr<MCCodeEmitter> Emitter,
                 MCAssembler *Assembler)
    : MCELFStreamer(Context, std::move(TAB), std::move(OW),
                    std::move(Emitter)),
      MCII(createSymphonyMCInstrInfo()) {}

  void
emitValueForModiferKind(const MCSymbol *Sym, unsigned SizeInBytes,
                        SMLoc Loc = SMLoc());
};


MCStreamer *createSymphonyELFStreamer(Triple const &TT, MCContext &Context,
                                 std::unique_ptr<MCAsmBackend> MAB,
                                 std::unique_ptr<MCObjectWriter> OW,
                                 std::unique_ptr<MCCodeEmitter> CE);
}

#endif
