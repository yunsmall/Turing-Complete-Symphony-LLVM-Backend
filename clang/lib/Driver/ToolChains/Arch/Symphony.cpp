#include "Symphony.h"
#include "clang/Driver/CommonArgs.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"
// #include "llvm/TargetParser/AArch64TargetParser.h"
#include "llvm/TargetParser/Host.h"

using namespace clang::driver;
using namespace clang::driver::tools;
using namespace clang;
using namespace llvm::opt;

std::string symphony::getSymphonyTargetCPU(const llvm::opt::ArgList &Args,
                                           const llvm::Triple &Triple) {
  // return "generic";
  return "";
}