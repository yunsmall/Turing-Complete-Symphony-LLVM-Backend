    .global _start
    .type	_start,@function
    .section	.text._start
_start:
	call main
	
_start_endless_loop:
	jmp _start_endless_loop

