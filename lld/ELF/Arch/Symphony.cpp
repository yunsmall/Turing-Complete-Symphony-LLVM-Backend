#include "OutputSections.h"
#include "Symbols.h"
#include "SyntheticSections.h"
#include "Target.h"
#include "llvm/Support/Endian.h"

using namespace llvm;
using namespace llvm::support::endian;
using namespace llvm::ELF;
using namespace lld;
using namespace lld::elf;

namespace {
class Symphony : public TargetInfo {
public:
  explicit Symphony(Ctx &ctx) : TargetInfo(ctx) {}
  RelExpr getRelExpr(RelType type, const Symbol &s,
                     const uint8_t *loc) const override;
  void relocate(uint8_t *loc, const Relocation &rel,
                uint64_t val) const override;
};
RelExpr Symphony::getRelExpr(RelType type, const Symbol &s,
                             const uint8_t *loc) const {
  switch (type) {
  case R_SYMPHONY_ABS:
    return R_ABS;
  default:
    Err(ctx) << getErrorLoc(ctx, loc) << "unknown relocation (" << type.v
             << ") against symbol " << &s;
    return R_NONE;
  }
}
void Symphony::relocate(uint8_t *loc, const Relocation &rel,
                        uint64_t val) const {
  write16be(loc, val);
}
} // namespace
void elf::setSymphonyTargetInfo(Ctx &ctx) {
  ctx.target.reset(new Symphony(ctx));
}
