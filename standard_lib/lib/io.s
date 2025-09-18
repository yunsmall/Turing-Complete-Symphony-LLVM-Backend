    .global in
    .global out
    .global init_console
    .global time
    .global keyboard
    .text
in:
    in r1
    ret

out:
    out r1
    mov r1,0
    ret

init_console:
    mov r1,0
    store_16 [32768],r1
    console 32770
    ret

time:
    sub sp,sp,2
    mov r2,r1

    time_3 r1
    store_16 [r2],r1

    add r2,r2,2
    time_2 r1
    store_16 [r2],r1

    add r2,r2,2
    time_1 r1
    store_16 [r2],r1

    add r2,r2,2
    time_0 r1
    store_16 [r2],r1

    add sp,sp,2
    ret

keyboard:
    keyboard r1
    ret