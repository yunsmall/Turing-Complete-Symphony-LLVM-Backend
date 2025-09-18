class SymphonyReg<string n, bits<4> num> : Register<n> {
  let Namespace = "Symphony";
  let HWEncoding{3-0} = num;
}



def ZR     : SymphonyReg<"zr",     0b0000>{
    let isConstant = true;
}
def R1     : SymphonyReg<"r1",     0b0001>;
def R2     : SymphonyReg<"r2",     0b0010>;
def R3     : SymphonyReg<"r3",     0b0011>;
def R4     : SymphonyReg<"r4",     0b0100>;
def R5     : SymphonyReg<"r5",     0b0101>;
def R6     : SymphonyReg<"r6",     0b0110>;
def R7     : SymphonyReg<"r7",     0b0111>;
def R8     : SymphonyReg<"r8",     0b1000>;
def R9     : SymphonyReg<"r9",     0b1001>;
def R10    : SymphonyReg<"r10",    0b1010>;
def R11    : SymphonyReg<"r11",    0b1011>;
def R12    : SymphonyReg<"r12",    0b1100>;
def R13    : SymphonyReg<"r13",    0b1101>;
def SP     : SymphonyReg<"sp",     0b1110>;
def FLAGS  : SymphonyReg<"flags",  0b1111>;


def GPR : RegisterClass<"Symphony", [i16], 16,
  (add ZR, (sequence "R%i", 1, 13), SP, FLAGS)>{}

def GPRNoZR : RegisterClass<"Symphony", [i16], 16,
  (add (sequence "R%i", 1, 13), SP, FLAGS)>;

def SPReg : RegisterClass<"Symphony", [i16], 16, (add SP)>;

def FlagsReg : RegisterClass<"Symphony", [i16], 16, (add FLAGS)>;