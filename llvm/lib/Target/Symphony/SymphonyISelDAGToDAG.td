// 定义复杂的模式匹配规则
def : Pat<(not (and GPR:$b, GPR:$c)),
          (NANDrrr GPR:$a, GPR:$b, GPR:$c)>;
          
def : Pat<(not (or GPR:$b, GPR:$c)),
          (NORrrr GPR:$a, GPR:$b, GPR:$c)>;

// 伪指令扩展模式
def : Pat<(store GPR:$value, (add SP, -2)),
          (PUSH GPR:$value)>;
          
def : Pat<(load (add SP, 2)),
          (POP GPR:$a)>;
