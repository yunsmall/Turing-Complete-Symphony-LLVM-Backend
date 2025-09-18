; ModuleID = '.\shift_test.c'
source_filename = ".\\shift_test.c"
target datalayout = "e-P1-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n8-a:8"
target triple = "avr"

; Function Attrs: noinline nounwind optnone
define dso_local void @put(i8 noundef signext %0, ptr noundef %1) addrspace(1) #0 {
  %3 = alloca i8, align 1
  %4 = alloca ptr, align 1
  store i8 %0, ptr %3, align 1
  store ptr %1, ptr %4, align 1
  %5 = load i8, ptr %3, align 1
  %6 = load ptr, ptr %4, align 1
  store i8 %5, ptr %6, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @show(i8 noundef signext %0) addrspace(1) #0 {
  %2 = alloca i8, align 1
  %3 = alloca ptr, align 1
  %4 = alloca i16, align 1
  %5 = alloca ptr, align 1
  store i8 %0, ptr %2, align 1
  store ptr inttoptr (i16 -32768 to ptr), ptr %3, align 1
  %6 = load ptr, ptr %3, align 1
  %7 = load i16, ptr %6, align 1
  store i16 %7, ptr %4, align 1
  %8 = load i16, ptr %4, align 1
  %9 = sext i16 %8 to i32
  %10 = add nsw i32 32770, %9
  %11 = trunc i32 %10 to i16
  %12 = inttoptr i16 %11 to ptr
  store ptr %12, ptr %5, align 1
  %13 = load i8, ptr %2, align 1
  %14 = load ptr, ptr %5, align 1
  call addrspace(1) void @put(i8 noundef signext %13, ptr noundef %14) #1
  %15 = load ptr, ptr %3, align 1
  %16 = load i16, ptr %15, align 1
  %17 = add nsw i16 %16, 1
  store i16 %17, ptr %15, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @show_num(i8 noundef zeroext %0) addrspace(1) #0 {
  %2 = alloca i8, align 1
  store i8 %0, ptr %2, align 1
  %3 = load i8, ptr %2, align 1
  %4 = zext i8 %3 to i16
  %5 = sdiv i16 %4, 100
  %6 = add nsw i16 %5, 48
  %7 = trunc i16 %6 to i8
  call addrspace(1) void @show(i8 noundef signext %7) #1
  %8 = load i8, ptr %2, align 1
  %9 = zext i8 %8 to i16
  %10 = srem i16 %9, 100
  %11 = sdiv i16 %10, 10
  %12 = add nsw i16 %11, 48
  %13 = trunc i16 %12 to i8
  call addrspace(1) void @show(i8 noundef signext %13) #1
  %14 = load i8, ptr %2, align 1
  %15 = zext i8 %14 to i16
  %16 = srem i16 %15, 10
  %17 = add nsw i16 %16, 48
  %18 = trunc i16 %17 to i8
  call addrspace(1) void @show(i8 noundef signext %18) #1
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @test() addrspace(1) #0 {
  call addrspace(1) void @show_num(i8 noundef zeroext 12) #1
  call addrspace(1) void @show_num(i8 noundef zeroext 123) #1
  ret void
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-builtins" "no-jump-tables"="true" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nobuiltin "no-builtins" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 2}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.7"}
