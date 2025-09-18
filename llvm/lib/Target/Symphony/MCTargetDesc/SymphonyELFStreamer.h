#ifndef LLVM_SYMPHONY_ELF_STREAMER_H
#define LLVM_SYMPHONY_ELF_STREAMER_H

#include "SymphonyTargetStreamer.h"

namespace llvm {

/// A target streamer for an AVR ELF object file.
class SymphonyELFStreamer : public SymphonyTargetStreamer {
public:
  SymphonyELFStreamer(MCStreamer &S, const MCSubtargetInfo &STI);

  MCELFStreamer &getStreamer() {
    return static_cast<MCELFStreamer &>(Streamer);
  }
};

} // end namespace llvm

#endif
