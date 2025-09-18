#include "SymphonySubtarget.h"

using namespace llvm;

#define DEBUG_TYPE "symphony-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SymphonyGenSubtargetInfo.inc"

SymphonySubtarget::SymphonySubtarget(const Triple &TT, StringRef CPU,
                                     StringRef FS, const TargetMachine &TM)
    : SymphonyGenSubtargetInfo(TT, CPU, CPU, FS), RegInfo(*this),
      FrameLowering(*this), TLI(TM, *this) {
  TSInfo = std::make_unique<SelectionDAGTargetInfo>();
}

SymphonySubtarget &
SymphonySubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS,
                                                   const TargetMachine &TM) {
  if (CPU.empty()) {
    CPU = "symphony";
  }
  ParseSubtargetFeatures(CPU, CPU, FS);
  return *this;
}
const SymphonyRegisterInfo *SymphonySubtarget::getRegisterInfo() const {
  return &RegInfo;
}
const SymphonyInstrInfo *SymphonySubtarget::getInstrInfo() const {
  return &InstrInfo;
}
const TargetFrameLowering *SymphonySubtarget::getFrameLowering() const {
  return &FrameLowering;
}
const TargetLowering *SymphonySubtarget::getTargetLowering() const {
  return &TLI;
}
const SelectionDAGTargetInfo *SymphonySubtarget::getSelectionDAGInfo() const {
  return TSInfo.get();
}