#include "MCTargetDesc/SymphonyMCTargetDesc.h"
#include "Symphony.h"
#include "SymphonySubtarget.h"
#include "SymphonyTargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

#define DEBUG_TYPE "symphony-isel"
#define PASS_NAME "Symphony DAG->DAG Pattern Instruction Selection"

class SymphonyDAGToDAGISel : public SelectionDAGISel {
public:
  SymphonyDAGToDAGISel() = delete;

  explicit SymphonyDAGToDAGISel(SymphonyTargetMachine &TM, CodeGenOptLevel OL)
      : SelectionDAGISel(TM, OL), Subtarget(nullptr) {}

  bool runOnMachineFunction(MachineFunction &MF) override;

private:
  const SymphonySubtarget *Subtarget;

#include "SymphonyGenDAGISel.inc"

  const SymphonyTargetMachine &getTargetMachine() {
    return static_cast<const SymphonyTargetMachine &>(TM);
  }

  void Select(SDNode *Node) override;

  bool trySelect(SDNode *N);
  template <unsigned NodeType> bool select(SDNode *N);

  bool SelectRIAddr(SDValue N, SDValue &Base, SDValue &Offset);
  bool SelectFrameAddr(SDValue RIAddr, SDValue &Base, SDValue &Offset);
};

bool SymphonyDAGToDAGISel::SelectRIAddr(SDValue N, SDValue &Base,
                                        SDValue &Offset) {
  return false;
}

// 选出add或sub的frameindex
bool SymphonyDAGToDAGISel::SelectFrameAddr(SDValue RIAddr, SDValue &Base,
                                           SDValue &Offset) {
  // 获取当前操作数的类型
  EVT ValTy = RIAddr.getValueType();
  SDLoc DL(RIAddr);

  if (auto *FIN = dyn_cast<FrameIndexSDNode>(RIAddr)) {
    Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), RIAddr.getValueType());
    Offset = CurDAG->getTargetConstant(0, DL, ValTy);
    return true;
  }

  if (RIAddr.getOpcode() != ISD::ADD && RIAddr.getOpcode() != ISD::SUB &&
      !CurDAG->isBaseWithConstantOffset(RIAddr)) {
    return false;
  }

  if (const ConstantSDNode *RHS =
          dyn_cast<ConstantSDNode>(RIAddr.getOperand(1))) {
    int RHSC = (int)RHS->getZExtValue();

    // <#Frame index + const>
    // Allow folding offsets bigger than 63 so the frame pointer can be used
    // directly instead of copying it around by adjusting and restoring it for
    // each access.
    if (RIAddr.getOperand(0).getOpcode() == ISD::FrameIndex) {
      int FI = cast<FrameIndexSDNode>(RIAddr.getOperand(0))->getIndex();

      Base = CurDAG->getTargetFrameIndex(FI, ValTy);
      Offset = CurDAG->getTargetConstant(RHSC, DL, MVT::i16);

      return true;
    }
  }

  return false;
}

// 选出单个的frameindex
template <> bool SymphonyDAGToDAGISel::select<ISD::FrameIndex>(SDNode *N) {
  auto DL = CurDAG->getDataLayout();

  // Convert the frameindex into a temp instruction that will hold the
  // effective address of the final stack slot.
  int FI = cast<FrameIndexSDNode>(N)->getIndex();
  // CurDAG->isBaseWithConstantOffset();
  SDValue TFI =
      CurDAG->getTargetFrameIndex(FI, getTargetLowering()->getPointerTy(DL));

  // CurDAG->SelectNodeTo(N, Symphony::frameptrget,
  //                      getTargetLowering()->getPointerTy(DL), TFI,
  //                      CurDAG->getTargetConstant(0, SDLoc(N), MVT::i16));
  CurDAG->SelectNodeTo(N, Symphony::frameptrget,
                       getTargetLowering()->getPointerTy(DL), TFI);
  // CurDAG->SelectNodeTo(N, Symphony::MOVI,
  // getTargetLowering()->getPointerTy(DL),
  //                      TFI);
  return true;
}

bool SymphonyDAGToDAGISel::trySelect(SDNode *N) {
  unsigned Opcode = N->getOpcode();

  switch (Opcode) {
  // case ISD::FrameIndex:
  //   return this->select<ISD::FrameIndex>(N);
  default:
    return false;
  }
}

bool SymphonyDAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &MF.getSubtarget<SymphonySubtarget>();
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void SymphonyDAGToDAGISel::Select(SDNode *Node) {
  SDLoc DL(Node);
  LLVM_DEBUG(dbgs() << "Selecting: "; Node->dump(CurDAG); dbgs() << "\n");

  if (trySelect(Node))
    return;

  SelectCode(Node);
}

class SymphonyDAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;
  explicit SymphonyDAGToDAGISelLegacy(SymphonyTargetMachine &TM)
      : SelectionDAGISelLegacy(
            ID, std::make_unique<SymphonyDAGToDAGISel>(TM, TM.getOptLevel())) {}
};

char SymphonyDAGToDAGISelLegacy::ID;

INITIALIZE_PASS(SymphonyDAGToDAGISelLegacy, DEBUG_TYPE, PASS_NAME, false,
                false);

FunctionPass *llvm::createSymphonyISelDag(SymphonyTargetMachine &TM) {
  return new SymphonyDAGToDAGISelLegacy(TM);
}
