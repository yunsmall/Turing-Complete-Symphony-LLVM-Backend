add_llvm_component_group(Symphony)


set (LLVM_TARGET_DEFINITIONS Symphony.td)

tablegen(LLVM SymphonyGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM SymphonyGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SymphonyGenDAGISel.inc -gen-dag-isel)
#tablegen(LLVM SymphonyGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM SymphonyGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SymphonyGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SymphonyGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SymphonyGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SymphonyGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM SymphonyGenMCCodeEmitter.inc -gen-emitter)

# SymphonyCommonTableGen must be defined
add_public_tablegen_target(SymphonyCommonTableGen)

# SymphonyCodeGen should match with LLVMBuild.txt SymphonyCodeGen
add_llvm_target(SymphonyCodeGen
        SymphonyTargetMachine.cpp
        SymphonyInstrInfo.cpp
        SymphonyRegisterInfo.cpp
        SymphonySubtarget.cpp
        SymphonyFrameLowering.cpp
        SymphonyISelLowering.cpp
        SymphonyISelDAGToDAG.cpp
        SymphonyAsmPrinter.cpp
        SymphonyExpandPseudoInsts.cpp

        LINK_COMPONENTS
        Support
        SymphonyInfo
        SymphonyDesc

        ADD_TO_COMPONENT
        Symphony
)

# Should match with "subdirectories = MCTargetDesc TargetInfo" in LLVMBuild.txt
add_subdirectory(AsmParser)
#add_subdirectory(Disassembler)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)