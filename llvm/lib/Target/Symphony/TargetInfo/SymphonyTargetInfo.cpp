#include "Symphony.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheSymphonyTarget() {
  static Target TheSymphonyTarget;
  return TheSymphonyTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSymphonyTargetInfo() {
  RegisterTarget<Triple::symphony, /*HasJIT=*/true> X(
      getTheSymphonyTarget(), "symphony",
      "Turing Complete game 16bits Symphony architecture", "Symphony");
}