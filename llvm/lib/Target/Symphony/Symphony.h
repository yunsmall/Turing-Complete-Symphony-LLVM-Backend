#ifndef LLVM_LIB_TARGET_SYMPHONY_SYMPHONY_H
#define LLVM_LIB_TARGET_SYMPHONY_SYMPHONY_H

#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

#define DIV_ROUND_UP(n, d)  (((n) + (d) - 1) / (d))
#define ROUND_UP(x, align)  (DIV_ROUND_UP(x, align) * (align))

class PassRegistry;
class SymphonyTargetMachine;
class FunctionPass;

FunctionPass *createSymphonyISelDag(SymphonyTargetMachine &TM);
FunctionPass *createSymphonyExpandPseudoPass();

void initializeSymphonyDAGToDAGISelLegacyPass(PassRegistry &);
void initializeSymphonyExpandPseudoPass(PassRegistry &);
} // namespace llvm

#endif
