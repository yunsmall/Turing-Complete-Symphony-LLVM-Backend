#include "MCTargetDesc/SymphonyMCELFStreamer.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSymbol.h"

#define DEBUG_TYPE "symphonymcelfstreamer"

using namespace llvm;

void SymphonyMCELFStreamer::emitValueForModiferKind(const MCSymbol *Sym,
                                                    unsigned SizeInBytes,
                                                    SMLoc Loc) {
  MCELFStreamer::emitValue(MCSymbolRefExpr::create(Sym, 0, getContext()),
                           SizeInBytes, Loc);
}

namespace llvm {
MCStreamer *createSymphonyELFStreamer(Triple const &TT, MCContext &Context,
                                      std::unique_ptr<MCAsmBackend> MAB,
                                      std::unique_ptr<MCObjectWriter> OW,
                                      std::unique_ptr<MCCodeEmitter> CE) {
  return new SymphonyMCELFStreamer(Context, std::move(MAB), std::move(OW),
                                   std::move(CE));
}

}
