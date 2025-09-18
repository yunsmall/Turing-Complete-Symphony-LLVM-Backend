#ifndef SYMPHONYSUBTARGET_H
#define SYMPHONYSUBTARGET_H

#include "SymphonyInstrInfo.h"
#include "SymphonyRegisterInfo.h"
#include "SymphonyFrameLowering.h"
#include "SymphonyISelLowering.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "SymphonyGenSubtargetInfo.inc"

namespace llvm {

class SymphonySubtarget : public SymphonyGenSubtargetInfo {
private:
  SymphonyRegisterInfo RegInfo;
  SymphonyInstrInfo InstrInfo;
  SymphonyFrameLowering FrameLowering;
  SymphonyTargetLowering TLI;
public:
  SymphonySubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                    const TargetMachine &TM);
  SymphonySubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS,
                                                    const TargetMachine &TM);
  const SymphonyRegisterInfo *getRegisterInfo() const override;
  const SymphonyInstrInfo *getInstrInfo() const override;
  const TargetFrameLowering *getFrameLowering() const override;
  const TargetLowering *getTargetLowering() const override;
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override;

protected:
  std::unique_ptr<SelectionDAGTargetInfo> TSInfo = nullptr;
};

} // namespace llvm

#endif // SYMPHONYSUBTARGET_H
