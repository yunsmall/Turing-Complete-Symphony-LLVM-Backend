#ifndef LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_SYMPHONY_H
#define LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_SYMPHONY_H

#include "clang/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"
#include <string>
#include <vector>

namespace clang {
namespace driver {
namespace tools {
namespace symphony {
std::string getSymphonyTargetCPU(const llvm::opt::ArgList &Args,
                                 const llvm::Triple &Triple);
}
} // namespace tools
} // namespace driver
} // namespace clang
#endif // LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_SYMPHONY_H
