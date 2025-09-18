#ifndef LLVM_SYMPHONY_MCEXPR_H
#define LLVM_SYMPHONY_MCEXPR_H

#include "llvm/MC/MCExpr.h"

namespace llvm {

class SymphonyMCExpr : public MCSpecifierExpr {
public:
  using Specifier = Spec;
public:
  /// Creates an AVR machine code expression.
  static const SymphonyMCExpr *create(Specifier S, const MCExpr *Expr, MCContext &Ctx);


private:
  explicit SymphonyMCExpr(Specifier S, const MCExpr *Expr)
      : MCSpecifierExpr(Expr, S){}
};

}

#endif
