#ifndef LLVM_LIB_TARGET_SYMPHONY_SYMPHONYTARGETMACHINE_H
#define LLVM_LIB_TARGET_SYMPHONY_SYMPHONYTARGETMACHINE_H

#include "SymphonySubtarget.h"

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class SymphonyTargetMachine :public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  SymphonySubtarget Subtarget;
public:
  SymphonyTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                        StringRef FS, const TargetOptions &Options,
                        std::optional<Reloc::Model> RM,
                        std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                        bool JIT);
  const TargetSubtargetInfo *getSubtargetImpl(const Function &) const override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};
}



#endif