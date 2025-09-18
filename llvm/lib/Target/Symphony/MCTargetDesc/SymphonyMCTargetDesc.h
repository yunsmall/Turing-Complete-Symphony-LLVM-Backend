#ifndef LLVM_LIB_TARGET_SYMPHONY_MCTARGETDESC_SYMPHONYMCTARGETDESC_H
#define LLVM_LIB_TARGET_SYMPHONY_MCTARGETDESC_SYMPHONYMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;

MCInstrInfo *createSymphonyMCInstrInfo();

MCCodeEmitter *createSymphonyMCCodeEmitter(const MCInstrInfo &MCII,
                                           MCContext &Ctx);

std::unique_ptr<MCObjectTargetWriter>
createSymphonyELFObjectWriter(const Triple &TT);

MCAsmBackend *createSymphonyAsmBackend(const Target &T,
                                       const MCSubtargetInfo &STI,
                                       const MCRegisterInfo &MRI,
                                       const llvm::MCTargetOptions &TO);

Target &getTheSymphonyTarget();
} // namespace llvm

#define GET_REGINFO_ENUM
#include "SymphonyGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "SymphonyGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "SymphonyGenSubtargetInfo.inc"

#endif
