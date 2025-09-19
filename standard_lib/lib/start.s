    .global _start
    .type	_start,@function
    .section	.text._start
_start:
    mov sp,0
	mov flags,0
	call main
	
_start_endless_loop:
	jmp _start_endless_loop

