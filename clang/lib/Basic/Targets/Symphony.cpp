#include "Symphony.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;
void SymphonyTargetInfo::getTargetDefines(const LangOptions &Opts,
                                          MacroBuilder &Builder) const {
  Builder.defineMacro("SYMPHONY");
  Builder.defineMacro("__SYMPHONY");
  Builder.defineMacro("__SYMPHONY__");

  Builder.defineMacro("__SYMPHONY_HAVE_CMOV__");
  Builder.defineMacro("__SYMPHONY_ALU_HAVE_UDIV__");
  Builder.defineMacro("__SYMPHONY_ALU_HAVE_UREM__");
  Builder.defineMacro("__SYMPHONY_ALU_HAVE_ASR__");
}
llvm::SmallVector<Builtin::InfosShard>
SymphonyTargetInfo::getTargetBuiltins() const {
  return {};
}
TargetInfo::BuiltinVaListKind SymphonyTargetInfo::getBuiltinVaListKind() const {
  return TargetInfo::VoidPtrBuiltinVaList;
}
bool SymphonyTargetInfo::validateAsmConstraint(
    const char *&Name, TargetInfo::ConstraintInfo &info) const {
  return false;
}
std::string_view SymphonyTargetInfo::getClobbers() const { return ""; }
bool SymphonyTargetInfo::setCPU(const std::string &Name) {
  CPU = Name;
  return true;
}
ArrayRef<const char *> SymphonyTargetInfo::getGCCRegNames() const {
  static const char *const GCCRegNames[] = {
      "zr", "r1", "r2",  "r3",  "r4",  "r5",  "r6", "r7",
      "r8", "r9", "r10", "r11", "r12", "r13", "sp", "flags"};
  return llvm::ArrayRef(GCCRegNames);
}
ArrayRef<TargetInfo::GCCRegAlias> SymphonyTargetInfo::getGCCRegAliases() const {
  return {};
}