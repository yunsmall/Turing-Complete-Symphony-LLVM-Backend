#include "SymphonyMCTargetDesc.h"

#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
// #include "llvm/Support/TargetRegistry.h"

#include "SymphonyELFStreamer.h"
#include "SymphonyInstPrinter.h"
#include "SymphonyInstrInfo.h"
#include "SymphonyMCAsmInfo.h"
#include "SymphonyRegisterInfo.h"
#include "SymphonySubtarget.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "SymphonyGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SymphonyGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SymphonyGenRegisterInfo.inc"

MCAsmInfo *createSymphonyMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT,
                                   const MCTargetOptions &Options) {
  return new SymphonyMCAsmInfo(TT);
}

MCRegisterInfo *createSymphonyMCRegisterInfo(const Triple &TT) {
  auto x = new MCRegisterInfo();
  InitSymphonyMCRegisterInfo(x, Symphony::R1);
  return x;
}

MCInstrInfo *llvm::createSymphonyMCInstrInfo() {
  auto x = new MCInstrInfo();
  InitSymphonyMCInstrInfo(x);
  return x;
}

MCSubtargetInfo *createSymphonyMCSubtargetInfo(const Triple &TT, StringRef CPU,
                                               StringRef FS) {
  if (CPU.empty()) {
    CPU = "symphony";
  }
  return createSymphonyMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

MCInstPrinter *createSymphonyMCInstPrinter(const Triple &T,
                                           unsigned SyntaxVariant,
                                           const MCAsmInfo &MAI,
                                           const MCInstrInfo &MII,
                                           const MCRegisterInfo &MRI) {
  return new SymphonyInstPrinter(MAI, MII, MRI);
}

static MCStreamer *createMCStreamer(const Triple &T, MCContext &Context,
                                    std::unique_ptr<MCAsmBackend> &&MAB,
                                    std::unique_ptr<MCObjectWriter> &&OW,
                                    std::unique_ptr<MCCodeEmitter> &&Emitter) {
  return createELFStreamer(Context, std::move(MAB), std::move(OW),
                           std::move(Emitter));
}

static MCTargetStreamer *
createSymphonyObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  return new SymphonyELFStreamer(S, STI);
}

static MCTargetStreamer *
createSymphonyTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS,
                                MCInstPrinter *InstPrint) {
  return new SymphonyTargetAsmStreamer(S, OS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSymphonyTargetMC() {
  TargetRegistry::RegisterMCAsmInfo(getTheSymphonyTarget(),
                                    createSymphonyMCAsmInfo);
  TargetRegistry::RegisterMCRegInfo(getTheSymphonyTarget(),
                                    createSymphonyMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(getTheSymphonyTarget(),
                                      createSymphonyMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(getTheSymphonyTarget(),
                                          createSymphonyMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(getTheSymphonyTarget(),
                                        createSymphonyMCInstPrinter);
  // TargetRegistry::RegisterAsmStreamer()
  TargetRegistry::RegisterAsmTargetStreamer(getTheSymphonyTarget(),
                                            createSymphonyTargetAsmStreamer);
  TargetRegistry::RegisterELFStreamer(getTheSymphonyTarget(), createMCStreamer);
  TargetRegistry::RegisterObjectTargetStreamer(
      getTheSymphonyTarget(), createSymphonyObjectTargetStreamer);
  TargetRegistry::RegisterMCCodeEmitter(getTheSymphonyTarget(),
                                        createSymphonyMCCodeEmitter);
  TargetRegistry::RegisterMCAsmBackend(getTheSymphonyTarget(),
                                       createSymphonyAsmBackend);
}
