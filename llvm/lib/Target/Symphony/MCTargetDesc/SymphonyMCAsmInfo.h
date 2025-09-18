#ifndef SYMPHONYMCASMINFO_H
#define SYMPHONYMCASMINFO_H

#include "SymphonyMCExpr.h"
#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;
class SymphonyMCAsmInfo : public MCAsmInfoELF {
public:
  enum Kind {
    NONE = 0,
    CONSTANT,
    // CONVERT_TO_LEGAL_IDENTIFIER,
  };

  explicit SymphonyMCAsmInfo(const Triple &TagetTriple);
  void printSpecifierExpr(raw_ostream &,
                          const MCSpecifierExpr &) const override;
private:
  void printSymbolRefExpr(raw_ostream &OS, const MCSymbolRefExpr &) const;
};

} // namespace llvm

#endif // SYMPHONYMCASMINFO_H
