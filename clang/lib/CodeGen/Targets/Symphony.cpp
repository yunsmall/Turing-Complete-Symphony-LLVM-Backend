#include "ABIInfoImpl.h"
#include "TargetInfo.h"
#include "clang/Basic/DiagnosticFrontend.h"

using namespace clang;
using namespace clang::CodeGen;


namespace {
class SymphonyABIInfo : public DefaultABIInfo {
public:
  explicit SymphonyABIInfo(CodeGen::CodeGenTypes &CGT) : DefaultABIInfo(CGT) {}
};
}
namespace {
class SymphonyTargetCodeGenInfo : public TargetCodeGenInfo {
public:
  explicit SymphonyTargetCodeGenInfo(CodeGen::CodeGenTypes &CGT)
      : TargetCodeGenInfo(std::make_unique<SymphonyABIInfo>(CGT)) {}
};
}
std::unique_ptr<TargetCodeGenInfo>
CodeGen::createSymphonyTargetCodeGenInfo(CodeGenModule &CGM) {
  return std::make_unique<SymphonyTargetCodeGenInfo>(CGM.getTypes());
}
