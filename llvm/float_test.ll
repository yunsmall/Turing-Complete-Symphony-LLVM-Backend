; ModuleID = '.\float_test.c'
source_filename = ".\\float_test.c"
target datalayout = "E-m:e-p:32:16:32-i8:8:8-i16:16:16-i32:16:32-n8:16:32-a:0:16-S16"
target triple = "m68k"

; Function Attrs: noinline nounwind optnone
define dso_local void @sum() #0 {
  %1 = alloca float, align 4
  %2 = alloca float, align 4
  store float 2.500000e-01, ptr %1, align 4
  %3 = load float, ptr %1, align 4
  %4 = fpext float %3 to double
  %5 = fadd double %4, 1.100000e-01
  %6 = fptrunc double %5 to float
  store float %6, ptr %2, align 4
  %7 = load float, ptr %1, align 4
  %8 = fdiv float %7, 3.000000e+00
  store float %8, ptr %1, align 4
  %9 = load float, ptr %1, align 4
  %10 = load float, ptr %2, align 4
  %11 = fadd float %10, %9
  store float %11, ptr %2, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local signext i16 @test() #0 {
  call void @sum() #1
  ret i16 0
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nobuiltin "no-builtins" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.7"}
