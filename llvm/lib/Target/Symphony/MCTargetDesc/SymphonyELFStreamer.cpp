#include "SymphonyELFStreamer.h"
#include "SymphonyMCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/TargetParser/SubtargetFeature.h"

namespace llvm {

SymphonyELFStreamer::SymphonyELFStreamer(MCStreamer &S, const MCSubtargetInfo &STI)
    : SymphonyTargetStreamer(S) {
  ELFObjectWriter &W = getStreamer().getWriter();
  unsigned EFlags = W.getELFHeaderEFlags();

  W.setELFHeaderEFlags(EFlags);
}

}
