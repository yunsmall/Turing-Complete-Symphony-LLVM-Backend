#include "SymphonyMCAsmInfo.h"

#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"

#include <regex>

using namespace llvm;

SymphonyMCAsmInfo::SymphonyMCAsmInfo(const Triple &TagetTriple) {
  CommentString = "//";
  PrivateLabelPrefix = "_";
}
void SymphonyMCAsmInfo::printSpecifierExpr(raw_ostream &OS,
                                           const MCSpecifierExpr &Expr) const {
  switch (Expr.getSpecifier()) {
  // case CONVERT_TO_LEGAL_IDENTIFIER: {
  //   auto *SubExpr = Expr.getSubExpr();
  //   if (auto SymbolRef = dyn_cast<MCSymbolRefExpr>(SubExpr)) {
  //     // printSymbolRefExpr(OS, *SymbolRef);
  //     printExpr(OS, *SubExpr);
  //   }
  //
  //   break;
  // }
  default:
    llvm_unreachable("invalid specifier");
  }
}
void SymphonyMCAsmInfo::printSymbolRefExpr(
    raw_ostream &OS, const MCSymbolRefExpr &SymbolRef) const {
  auto SymbolName = SymbolRef.getSymbol().getName();
  std::string StdStringSymbolName = SymbolName.str();
  std::replace(StdStringSymbolName.begin(), StdStringSymbolName.end(), '.',
               '_');
  OS << StdStringSymbolName;
}