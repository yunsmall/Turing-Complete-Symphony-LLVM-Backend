add_llvm_component_library(LLVMSymphonyDesc
        SymphonyMCTargetDesc.cpp
        SymphonyMCAsmInfo.cpp
        SymphonyInstPrinter.cpp
        SymphonyMCCodeEmitter.cpp
        SymphonyELFObjectWriter.cpp
        SymphonyMCELFStreamer.cpp
        SymphonyELFStreamer.cpp
        SymphonyTargetStreamer.cpp
        SymphonyMCExpr.cpp
        SymphonyAsmBackend.cpp

        LINK_COMPONENTS
        CodeGenTypes
        MC
        Support
        TargetParser

        ADD_TO_COMPONENT
        Symphony
)
