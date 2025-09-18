#include "SymphonyTargetMachine.h"
#include "Symphony.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
// #include "llvm/Support/T

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSymphonyTarget() {
  RegisterTargetMachine<SymphonyTargetMachine> X(getTheSymphonyTarget());
  auto *PR = PassRegistry::getPassRegistry();
  initializeSymphonyDAGToDAGISelLegacyPass(*PR);
  initializeSymphonyExpandPseudoPass(*PR);
}

static StringRef computeDataLayout(const Triple &TT,
                                   const TargetOptions &options) {
  assert(TT.isArch16Bit() && "symphony only supports 16 bit");
  return "E-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n16-S8";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

SymphonyTargetMachine::SymphonyTargetMachine(const Target &T, const Triple &TT,
                                             StringRef CPU, StringRef FS,
                                             const TargetOptions &Options,
                                             std::optional<Reloc::Model> RM,
                                             std::optional<CodeModel::Model> CM,
                                             CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT, Options), TT, CPU, FS,
                               Options, getEffectiveRelocModel(TT, RM),
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();

}
const TargetSubtargetInfo *
SymphonyTargetMachine::getSubtargetImpl(const Function &function) const {
  return &Subtarget;
}

namespace {
class SymphonyPassConfig : public TargetPassConfig {
public:
  SymphonyPassConfig(TargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}
  SymphonyTargetMachine &getSymphonyTargetMachine() const {
    return getTM<SymphonyTargetMachine>();
  }
  bool addInstSelector() override;

protected:
  void addPreSched2() override;
};

} // namespace

TargetPassConfig *SymphonyTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new SymphonyPassConfig(*this, PM);
}

bool SymphonyPassConfig::addInstSelector() {
  addPass(createSymphonyISelDag(getSymphonyTargetMachine()));
  return false;
}

void SymphonyPassConfig::addPreSched2() {
  addPass(createSymphonyExpandPseudoPass());
}