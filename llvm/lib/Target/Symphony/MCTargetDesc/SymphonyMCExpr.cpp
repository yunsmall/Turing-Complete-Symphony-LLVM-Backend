#include "SymphonyMCExpr.h"
#include "MCTargetDesc/SymphonyMCAsmInfo.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCValue.h"

namespace llvm {

const SymphonyMCExpr *SymphonyMCExpr::create(Specifier Kind, const MCExpr *Expr,
                                             MCContext &Ctx) {
  return new (Ctx) SymphonyMCExpr(Kind, Expr);
}

} // namespace llvm
