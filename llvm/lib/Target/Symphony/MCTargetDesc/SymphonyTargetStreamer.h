#ifndef LLVM_SYMPHONY_TARGET_STREAMER_H
#define LLVM_SYMPHONY_TARGET_STREAMER_H

#include "llvm/MC/MCELFStreamer.h"

namespace llvm {
class MCStreamer;
class formatted_raw_ostream;

class SymphonyTargetStreamer : public MCTargetStreamer {
public:
  explicit SymphonyTargetStreamer(MCStreamer &S);
};

class SymphonyTargetAsmStreamer : public SymphonyTargetStreamer {
  formatted_raw_ostream &OS;
public:
  SymphonyTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS)
      : SymphonyTargetStreamer(S), OS(OS) {}
};

}

#endif
