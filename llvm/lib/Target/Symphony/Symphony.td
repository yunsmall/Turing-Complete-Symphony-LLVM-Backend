include "llvm/Target/Target.td"

include "SymphonyRegisterInfo.td"
include "SymphonySchedule.td"
include "SymphonyInstrInfo.td"
include "SymphonyCallingConv.td"

def : Processor<"symphony",NoItineraries,[]>;

def SymphonyInstrInfo : InstrInfo;

def SymphonyAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = true;
  //let AllowDuplicateRegisterNames = true;
}

def Symphony : Target {
   let InstructionSet = SymphonyInstrInfo;
   let AssemblyParsers = [SymphonyAsmParser];
}