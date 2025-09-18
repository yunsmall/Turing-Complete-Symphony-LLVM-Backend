#include "SymphonyTargetStreamer.h"

#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/FormattedStream.h"

namespace llvm {

SymphonyTargetStreamer::SymphonyTargetStreamer(MCStreamer &S)
    : MCTargetStreamer(S) {}
}
