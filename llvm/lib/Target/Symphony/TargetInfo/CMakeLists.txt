add_llvm_component_library(LLVMSymphonyInfo
        SymphonyTargetInfo.cpp

        LINK_COMPONENTS
        MC
        Support

        ADD_TO_COMPONENT
        Symphony
)
