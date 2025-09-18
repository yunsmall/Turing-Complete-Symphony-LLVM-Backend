add_llvm_component_library(LLVMSymphonyAsmParser
  SymphonyAsmParser.cpp

  LINK_COMPONENTS
  SymphonyDesc
  SymphonyInfo
  CodeGenTypes
  MC
  MCParser
  Support

  ADD_TO_COMPONENT
  Symphony
  )
