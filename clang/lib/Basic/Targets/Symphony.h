#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_SYMPHONY_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_SYMPHONY_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {

// SYMPHONY Target
class LLVM_LIBRARY_VISIBILITY SymphonyTargetInfo : public TargetInfo {
public:
  SymphonyTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    BigEndian = true;
    TLSSupported = false;
    PointerWidth = 16;
    PointerAlign = 8;
    ShortWidth = 16;
    ShortAlign = 8;
    IntWidth = 16;
    IntAlign = 8;
    LongWidth = 32;
    LongAlign = 8;
    LongLongWidth = 64;
    LongLongAlign = 8;
    SuitableAlign = 8;
    DefaultAlignForAttributeAligned = 8;
    HalfWidth = 16;
    HalfAlign = 8;
    FloatWidth = 32;
    FloatAlign = 8;
    DoubleWidth = 64;
    DoubleAlign = 8;
    DoubleFormat = &llvm::APFloat::IEEEdouble();
    LongDoubleWidth = 128;
    LongDoubleAlign = 8;
    LongDoubleFormat = &llvm::APFloat::IEEEdouble();
    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;
    Char16Type = UnsignedInt;
    WIntType = SignedInt;
    Int16Type = SignedInt;
    Char32Type = UnsignedLong;
    SigAtomicType = SignedChar;
    resetDataLayout("E-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n16-S8");
  }
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;
  llvm::SmallVector<Builtin::InfosShard> getTargetBuiltins() const override;
  BuiltinVaListKind getBuiltinVaListKind() const override;
  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override;
  std::string_view getClobbers() const override;
  bool setCPU(const std::string &Name) override;

protected:

  std::string CPU;

  ArrayRef<const char *> getGCCRegNames() const override;
  ArrayRef<GCCRegAlias> getGCCRegAliases() const override;
};

} // namespace targets
} // namespace clang

#endif LLVM_CLANG_LIB_BASIC_TARGETS_SYMPHONY_H