; ModuleID = '.\game_npe.c'
source_filename = ".\\game_npe.c"
target datalayout = "E-m:e-p:32:16:32-i8:8:8-i16:16:16-i32:16:32-n8:16:32-a:0:16-S16"
target triple = "m68k"

%struct.data = type { i8, [3 x i8], %union.inner }
%union.inner = type { i32 }

@stack = external dso_local global ptr, align 4

; Function Attrs: noinline nounwind optnone
define dso_local zeroext i16 @input() #0 {
  %1 = alloca i16, align 2
  %2 = load i16, ptr %1, align 2
  ret i16 %2
}

; Function Attrs: noinline nounwind optnone
define dso_local void @output(i16 noundef zeroext %0) #0 {
  %2 = alloca i16, align 2
  store i16 %0, ptr %2, align 2
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local signext i8 @is_op(i16 noundef zeroext %0) #0 {
  %2 = alloca i8, align 1
  %3 = alloca i16, align 2
  store i16 %0, ptr %3, align 2
  %4 = load i16, ptr %3, align 2
  %5 = zext i16 %4 to i32
  switch i32 %5, label %7 [
    i32 43, label %6
    i32 45, label %6
    i32 124, label %6
    i32 38, label %6
    i32 94, label %6
    i32 60, label %6
    i32 62, label %6
  ]

6:                                                ; preds = %1, %1, %1, %1, %1, %1, %1
  store i8 1, ptr %2, align 1
  br label %8

7:                                                ; preds = %1
  store i8 0, ptr %2, align 1
  br label %8

8:                                                ; preds = %7, %6
  %9 = load i8, ptr %2, align 1
  ret i8 %9
}

; Function Attrs: noinline nounwind optnone
define dso_local zeroext i16 @do_calc(i32 noundef %0, i16 noundef zeroext %1, i16 noundef zeroext %2) #0 {
  %4 = alloca i16, align 2
  %5 = alloca i32, align 4
  %6 = alloca i16, align 2
  %7 = alloca i16, align 2
  store i32 %0, ptr %5, align 4
  store i16 %1, ptr %6, align 2
  store i16 %2, ptr %7, align 2
  %8 = load i32, ptr %5, align 4
  switch i32 %8, label %58 [
    i32 0, label %9
    i32 1, label %16
    i32 2, label %23
    i32 3, label %30
    i32 4, label %37
    i32 5, label %44
    i32 6, label %51
  ]

9:                                                ; preds = %3
  %10 = load i16, ptr %6, align 2
  %11 = zext i16 %10 to i32
  %12 = load i16, ptr %7, align 2
  %13 = zext i16 %12 to i32
  %14 = add nsw i32 %11, %13
  %15 = trunc i32 %14 to i16
  store i16 %15, ptr %4, align 2
  br label %59

16:                                               ; preds = %3
  %17 = load i16, ptr %6, align 2
  %18 = zext i16 %17 to i32
  %19 = load i16, ptr %7, align 2
  %20 = zext i16 %19 to i32
  %21 = sub nsw i32 %18, %20
  %22 = trunc i32 %21 to i16
  store i16 %22, ptr %4, align 2
  br label %59

23:                                               ; preds = %3
  %24 = load i16, ptr %6, align 2
  %25 = zext i16 %24 to i32
  %26 = load i16, ptr %7, align 2
  %27 = zext i16 %26 to i32
  %28 = or i32 %25, %27
  %29 = trunc i32 %28 to i16
  store i16 %29, ptr %4, align 2
  br label %59

30:                                               ; preds = %3
  %31 = load i16, ptr %6, align 2
  %32 = zext i16 %31 to i32
  %33 = load i16, ptr %7, align 2
  %34 = zext i16 %33 to i32
  %35 = and i32 %32, %34
  %36 = trunc i32 %35 to i16
  store i16 %36, ptr %4, align 2
  br label %59

37:                                               ; preds = %3
  %38 = load i16, ptr %6, align 2
  %39 = zext i16 %38 to i32
  %40 = load i16, ptr %7, align 2
  %41 = zext i16 %40 to i32
  %42 = xor i32 %39, %41
  %43 = trunc i32 %42 to i16
  store i16 %43, ptr %4, align 2
  br label %59

44:                                               ; preds = %3
  %45 = load i16, ptr %6, align 2
  %46 = zext i16 %45 to i32
  %47 = load i16, ptr %7, align 2
  %48 = zext i16 %47 to i32
  %49 = shl i32 %46, %48
  %50 = trunc i32 %49 to i16
  store i16 %50, ptr %4, align 2
  br label %59

51:                                               ; preds = %3
  %52 = load i16, ptr %6, align 2
  %53 = zext i16 %52 to i32
  %54 = load i16, ptr %7, align 2
  %55 = zext i16 %54 to i32
  %56 = ashr i32 %53, %55
  %57 = trunc i32 %56 to i16
  store i16 %57, ptr %4, align 2
  br label %59

58:                                               ; preds = %3
  store i16 0, ptr %4, align 2
  br label %59

59:                                               ; preds = %58, %51, %44, %37, %30, %23, %16, %9
  %60 = load i16, ptr %4, align 2
  ret i16 %60
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i16, align 2
  %3 = alloca i8, align 1
  %4 = alloca i16, align 2
  %5 = alloca i32, align 4
  %6 = alloca i16, align 2
  store i32 0, ptr %1, align 4
  store i16 0, ptr %2, align 2
  store i8 1, ptr %3, align 1
  br label %7

7:                                                ; preds = %0, %162
  %8 = call zeroext i16 @input() #1
  store i16 %8, ptr %4, align 2
  %9 = load i16, ptr %4, align 2
  %10 = zext i16 %9 to i32
  %11 = icmp ne i32 %10, 32
  br i1 %11, label %12, label %161

12:                                               ; preds = %7
  %13 = load i8, ptr %3, align 1
  %14 = icmp ne i8 %13, 0
  br i1 %14, label %15, label %160

15:                                               ; preds = %12
  %16 = load i16, ptr %4, align 2
  %17 = zext i16 %16 to i32
  %18 = icmp sle i32 48, %17
  br i1 %18, label %19, label %38

19:                                               ; preds = %15
  %20 = load i16, ptr %4, align 2
  %21 = zext i16 %20 to i32
  %22 = icmp sle i32 %21, 57
  br i1 %22, label %23, label %38

23:                                               ; preds = %19
  %24 = load ptr, ptr @stack, align 4
  %25 = load i16, ptr %2, align 2
  %26 = zext i16 %25 to i32
  %27 = getelementptr inbounds nuw %struct.data, ptr %24, i32 %26
  %28 = getelementptr inbounds nuw %struct.data, ptr %27, i32 0, i32 0
  store i8 1, ptr %28, align 4
  %29 = load i16, ptr %4, align 2
  %30 = zext i16 %29 to i32
  %31 = sub nsw i32 %30, 48
  %32 = trunc i32 %31 to i16
  %33 = load ptr, ptr @stack, align 4
  %34 = load i16, ptr %2, align 2
  %35 = zext i16 %34 to i32
  %36 = getelementptr inbounds nuw %struct.data, ptr %33, i32 %35
  %37 = getelementptr inbounds nuw %struct.data, ptr %36, i32 0, i32 2
  store i16 %32, ptr %37, align 4
  br label %157

38:                                               ; preds = %19, %15
  %39 = load i16, ptr %4, align 2
  %40 = call signext i8 @is_op(i16 noundef zeroext %39) #1
  %41 = icmp ne i8 %40, 0
  br i1 %41, label %42, label %156

42:                                               ; preds = %38
  %43 = load i16, ptr %4, align 2
  %44 = zext i16 %43 to i32
  %45 = icmp eq i32 %44, 43
  br i1 %45, label %46, label %47

46:                                               ; preds = %42
  store i32 0, ptr %5, align 4
  br label %85

47:                                               ; preds = %42
  %48 = load i16, ptr %4, align 2
  %49 = zext i16 %48 to i32
  %50 = icmp eq i32 %49, 45
  br i1 %50, label %51, label %52

51:                                               ; preds = %47
  store i32 1, ptr %5, align 4
  br label %84

52:                                               ; preds = %47
  %53 = load i16, ptr %4, align 2
  %54 = zext i16 %53 to i32
  %55 = icmp eq i32 %54, 124
  br i1 %55, label %56, label %57

56:                                               ; preds = %52
  store i32 2, ptr %5, align 4
  br label %83

57:                                               ; preds = %52
  %58 = load i16, ptr %4, align 2
  %59 = zext i16 %58 to i32
  %60 = icmp eq i32 %59, 38
  br i1 %60, label %61, label %62

61:                                               ; preds = %57
  store i32 0, ptr %5, align 4
  br label %82

62:                                               ; preds = %57
  %63 = load i16, ptr %4, align 2
  %64 = zext i16 %63 to i32
  %65 = icmp eq i32 %64, 94
  br i1 %65, label %66, label %67

66:                                               ; preds = %62
  store i32 4, ptr %5, align 4
  br label %81

67:                                               ; preds = %62
  %68 = load i16, ptr %4, align 2
  %69 = zext i16 %68 to i32
  %70 = icmp eq i32 %69, 60
  br i1 %70, label %71, label %73

71:                                               ; preds = %67
  store i32 5, ptr %5, align 4
  %72 = call zeroext i16 @input() #1
  br label %80

73:                                               ; preds = %67
  %74 = load i16, ptr %4, align 2
  %75 = zext i16 %74 to i32
  %76 = icmp eq i32 %75, 62
  br i1 %76, label %77, label %79

77:                                               ; preds = %73
  store i32 6, ptr %5, align 4
  %78 = call zeroext i16 @input() #1
  br label %79

79:                                               ; preds = %77, %73
  br label %80

80:                                               ; preds = %79, %71
  br label %81

81:                                               ; preds = %80, %66
  br label %82

82:                                               ; preds = %81, %61
  br label %83

83:                                               ; preds = %82, %56
  br label %84

84:                                               ; preds = %83, %51
  br label %85

85:                                               ; preds = %84, %46
  %86 = load ptr, ptr @stack, align 4
  %87 = load i16, ptr %2, align 2
  %88 = zext i16 %87 to i32
  %89 = getelementptr inbounds nuw %struct.data, ptr %86, i32 %88
  %90 = getelementptr inbounds nuw %struct.data, ptr %89, i32 0, i32 0
  store i8 0, ptr %90, align 4
  %91 = load i32, ptr %5, align 4
  %92 = load ptr, ptr @stack, align 4
  %93 = load i16, ptr %2, align 2
  %94 = zext i16 %93 to i32
  %95 = getelementptr inbounds nuw %struct.data, ptr %92, i32 %94
  %96 = getelementptr inbounds nuw %struct.data, ptr %95, i32 0, i32 2
  store i32 %91, ptr %96, align 4
  %97 = load i16, ptr %2, align 2
  %98 = zext i16 %97 to i32
  %99 = icmp sge i32 %98, 2
  br i1 %99, label %100, label %155

100:                                              ; preds = %85
  %101 = load ptr, ptr @stack, align 4
  %102 = load i16, ptr %2, align 2
  %103 = zext i16 %102 to i32
  %104 = sub nsw i32 %103, 2
  %105 = getelementptr inbounds %struct.data, ptr %101, i32 %104
  %106 = getelementptr inbounds nuw %struct.data, ptr %105, i32 0, i32 0
  %107 = load i8, ptr %106, align 4
  %108 = sext i8 %107 to i32
  %109 = icmp ne i32 %108, 0
  br i1 %109, label %110, label %154

110:                                              ; preds = %100
  %111 = load ptr, ptr @stack, align 4
  %112 = load i16, ptr %2, align 2
  %113 = zext i16 %112 to i32
  %114 = sub nsw i32 %113, 2
  %115 = getelementptr inbounds %struct.data, ptr %111, i32 %114
  %116 = getelementptr inbounds nuw %struct.data, ptr %115, i32 0, i32 0
  %117 = load i8, ptr %116, align 4
  %118 = sext i8 %117 to i32
  %119 = icmp ne i32 %118, 0
  br i1 %119, label %120, label %154

120:                                              ; preds = %110
  %121 = load ptr, ptr @stack, align 4
  %122 = load i16, ptr %2, align 2
  %123 = zext i16 %122 to i32
  %124 = getelementptr inbounds nuw %struct.data, ptr %121, i32 %123
  %125 = getelementptr inbounds nuw %struct.data, ptr %124, i32 0, i32 2
  %126 = load i32, ptr %125, align 4
  %127 = load ptr, ptr @stack, align 4
  %128 = load i16, ptr %2, align 2
  %129 = zext i16 %128 to i32
  %130 = sub nsw i32 %129, 2
  %131 = getelementptr inbounds %struct.data, ptr %127, i32 %130
  %132 = getelementptr inbounds nuw %struct.data, ptr %131, i32 0, i32 2
  %133 = load i16, ptr %132, align 4
  %134 = load ptr, ptr @stack, align 4
  %135 = load i16, ptr %2, align 2
  %136 = zext i16 %135 to i32
  %137 = sub nsw i32 %136, 1
  %138 = getelementptr inbounds %struct.data, ptr %134, i32 %137
  %139 = getelementptr inbounds nuw %struct.data, ptr %138, i32 0, i32 2
  %140 = load i16, ptr %139, align 4
  %141 = call zeroext i16 @do_calc(i32 noundef %126, i16 noundef zeroext %133, i16 noundef zeroext %140) #1
  store i16 %141, ptr %6, align 2
  %142 = load i16, ptr %6, align 2
  call void @output(i16 noundef zeroext %142) #1
  %143 = load i16, ptr %6, align 2
  %144 = load ptr, ptr @stack, align 4
  %145 = load i16, ptr %2, align 2
  %146 = zext i16 %145 to i32
  %147 = sub nsw i32 %146, 2
  %148 = getelementptr inbounds %struct.data, ptr %144, i32 %147
  %149 = getelementptr inbounds nuw %struct.data, ptr %148, i32 0, i32 2
  store i16 %143, ptr %149, align 4
  %150 = load i16, ptr %2, align 2
  %151 = zext i16 %150 to i32
  %152 = sub nsw i32 %151, 2
  %153 = trunc i32 %152 to i16
  store i16 %153, ptr %2, align 2
  br label %154

154:                                              ; preds = %120, %110, %100
  br label %155

155:                                              ; preds = %154, %85
  br label %156

156:                                              ; preds = %155, %38
  br label %157

157:                                              ; preds = %156, %23
  %158 = load i16, ptr %2, align 2
  %159 = add i16 %158, 1
  store i16 %159, ptr %2, align 2
  br label %160

160:                                              ; preds = %157, %12
  store i8 0, ptr %3, align 1
  br label %162

161:                                              ; preds = %7
  store i8 1, ptr %3, align 1
  br label %162

162:                                              ; preds = %161, %160
  br label %7
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-builtins" "no-jump-tables"="true" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nobuiltin "no-builtins" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.7"}
