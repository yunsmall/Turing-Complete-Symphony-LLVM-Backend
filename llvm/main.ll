; ModuleID = '.\float_test.c'
source_filename = ".\\float_test.c"
target datalayout = "E-m:e-p:32:16:32-i8:8:8-i16:16:16-i32:16:32-n8:16:32-a:0:16-S16"
target triple = "m68k"

; Function Attrs: noinline nounwind optnone
define dso_local void @sum(float noundef %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store float %0, ptr %2, align 4
  store float 2.500000e-01, ptr %3, align 4
  %5 = load float, ptr %3, align 4
  %6 = fpext float %5 to double
  %7 = fadd double %6, 1.100000e-01
  %8 = fptrunc double %7 to float
  store float %8, ptr %4, align 4
  %9 = load float, ptr %3, align 4
  %10 = fdiv float %9, 3.000000e+00
  store float %10, ptr %3, align 4
  %11 = load float, ptr %3, align 4
  %12 = load float, ptr %4, align 4
  %13 = fadd float %12, %11
  store float %13, ptr %4, align 4
  %14 = load float, ptr %2, align 4
  %15 = load float, ptr %4, align 4
  %16 = fsub float %15, %14
  store float %16, ptr %4, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local signext i16 @test() #0 {
  %1 = alloca float, align 4
  store float 0x400921CAC0000000, ptr %1, align 4
  %2 = load float, ptr %1, align 4
  call void @sum(float noundef %2) #1
  ret i16 0
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nobuiltin "no-builtins" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.7"}
