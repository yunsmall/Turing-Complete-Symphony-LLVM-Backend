#ifndef LLVM_LIB_TARGET_SYMPHONY_SYMPHONYFRAMELOWERING_H
#define LLVM_LIB_TARGET_SYMPHONY_SYMPHONYFRAMELOWERING_H

#include "Symphony.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class SymphonySubtarget;
class SymphonyFrameLowering : public TargetFrameLowering {
  const SymphonySubtarget &STI;
public:
  explicit SymphonyFrameLowering(const SymphonySubtarget &Subtarget)
      : TargetFrameLowering(StackDirection::StackGrowsDown, Align(2), 0,
                            Align(2), true),
        STI(Subtarget) {}
  uint64_t computeStackSize(MachineFunction &MF) const;
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
                            RegScavenger *RS) const override;

protected:
  [[nodiscard]] bool hasFPImpl(const MachineFunction &MF) const override;
};
} // namespace llvm

#endif // SYMPHONYFRAMELOWERING_H
