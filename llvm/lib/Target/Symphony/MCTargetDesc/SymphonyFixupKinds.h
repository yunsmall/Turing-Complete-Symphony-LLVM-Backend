#ifndef LLVM_SYMPHONY_FIXUP_KINDS_H
#define LLVM_SYMPHONY_FIXUP_KINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace Symphony {
enum Fixups {
  fixup_abs_jmp = FirstTargetFixupKind,
  fixup_abs_call,
  fixup_abs_mem,
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
}
}

#endif
