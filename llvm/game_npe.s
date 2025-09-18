	.file	"game_npe.c"
	.text
	.globl	input                           // -- Begin function input
	.type	input,@function
input:                                  // @input
// %bb.0:
	sub	sp, sp, 2
	add	r1, sp, 0
	load_16	r1, [r1]
	add	sp, sp, 2
	ret
.Lfunc_end0:
	.size	input, .Lfunc_end0-input
                                        // -- End function
	.globl	output                          // -- Begin function output
	.type	output,@function
output:                                 // @output
// %bb.0:
	sub	sp, sp, 2
	mov	r2, r1
	add	r1, sp, 0
	store_16	[r1], r2
	add	sp, sp, 2
	ret
.Lfunc_end1:
	.size	output, .Lfunc_end1-output
                                        // -- End function
	.globl	is_op                           // -- Begin function is_op
	.type	is_op,@function
is_op:                                  // @is_op
// %bb.0:
	sub	sp, sp, 8
	mov	r2, r1
	add	r1, sp, 4
	store_16	[r1], r2
	load_16	r1, [r1]
	mov	r13, sp
	store_16	[r13], r1
	mov	r2, 0
	add	r13, sp, 2
	store_16	[r13], r2
	cmp	r1, 38
	je	_BB2_1
	jmp _BB2_4
_BB2_4:
	add	r13, sp, 2
	load_16	r2, [r13]
	mov	r13, sp
	load_16	r1, [r13]
	xor	r1, r1, 43
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB2_1
	jmp _BB2_5
_BB2_5:
	add	r13, sp, 2
	load_16	r2, [r13]
	mov	r13, sp
	load_16	r1, [r13]
	xor	r1, r1, 45
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB2_1
	jmp _BB2_6
_BB2_6:
	add	r13, sp, 2
	load_16	r2, [r13]
	mov	r13, sp
	load_16	r1, [r13]
	xor	r1, r1, 60
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB2_1
	jmp _BB2_7
_BB2_7:
	add	r13, sp, 2
	load_16	r2, [r13]
	mov	r13, sp
	load_16	r1, [r13]
	xor	r1, r1, 62
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB2_1
	jmp _BB2_8
_BB2_8:
	add	r13, sp, 2
	load_16	r2, [r13]
	mov	r13, sp
	load_16	r1, [r13]
	xor	r1, r1, 94
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB2_1
	jmp _BB2_9
_BB2_9:
	add	r13, sp, 2
	load_16	r2, [r13]
	mov	r13, sp
	load_16	r1, [r13]
	xor	r1, r1, 124
	or	r1, r1, r2
	cmp	r1, 0
	jne	_BB2_2
	jmp _BB2_1
_BB2_1:
	mov	r2, 1
	add	r1, sp, 7
	store_8	[r1], r2
	jmp _BB2_3
_BB2_2:
	mov	r2, 0
	add	r1, sp, 7
	store_8	[r1], r2
	jmp _BB2_3
_BB2_3:
	add	r1, sp, 7
	load_8	r1, [r1]
	lsl	r1, r1, 8
	asr	r1, r1, 8
	add	sp, sp, 8
	ret
.Lfunc_end2:
	.size	is_op, .Lfunc_end2-is_op
                                        // -- End function
	.globl	do_calc                         // -- Begin function do_calc
	.type	do_calc,@function
do_calc:                                // @do_calc
// %bb.0:
	sub	sp, sp, 16
	mov	r5, r3
	mov	r3, r2
                                        // kill: def $r2 killed $r3
                                        // kill: def $r2 killed $r1
	add	r2, sp, 8
	store_16	[r2], r1
	or	r1, r2, 2
	store_16	[r1], r3
	add	r3, sp, 6
	store_16	[r3], r5
	add	r3, sp, 4
	store_16	[r3], r4
	load_16	r2, [r2]
	mov	r13, sp
	store_16	[r13], r2
	load_16	r1, [r1]
	add	r13, sp, 2
	store_16	[r13], r1
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_1
	jmp _BB3_10
_BB3_10:
	mov	r13, sp
	load_16	r2, [r13]
	add	r13, sp, 2
	load_16	r1, [r13]
	xor	r1, r1, 1
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_2
	jmp _BB3_11
_BB3_11:
	mov	r13, sp
	load_16	r2, [r13]
	add	r13, sp, 2
	load_16	r1, [r13]
	xor	r1, r1, 2
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_3
	jmp _BB3_12
_BB3_12:
	mov	r13, sp
	load_16	r2, [r13]
	add	r13, sp, 2
	load_16	r1, [r13]
	xor	r1, r1, 3
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_4
	jmp _BB3_13
_BB3_13:
	mov	r13, sp
	load_16	r2, [r13]
	add	r13, sp, 2
	load_16	r1, [r13]
	xor	r1, r1, 4
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_5
	jmp _BB3_14
_BB3_14:
	mov	r13, sp
	load_16	r2, [r13]
	add	r13, sp, 2
	load_16	r1, [r13]
	xor	r1, r1, 5
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_6
	jmp _BB3_15
_BB3_15:
	mov	r13, sp
	load_16	r2, [r13]
	add	r13, sp, 2
	load_16	r1, [r13]
	xor	r1, r1, 6
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB3_7
	jmp _BB3_8
_BB3_1:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	add	r2, r1, r2
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_2:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	sub	r2, r1, r2
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_3:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	or	r2, r1, r2
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_4:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	and	r2, r1, r2
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_5:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	xor	r2, r1, r2
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_6:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	lsl	r1, r1, r2
	add	r2, r2, 65520
	cmp	r2, 0
	mov	r2, 0
	cmovge	r2, r1
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_7:
	add	r1, sp, 6
	load_16	r1, [r1]
	add	r2, sp, 4
	load_16	r2, [r2]
	lsr	r1, r1, r2
	add	r2, r2, 65520
	cmp	r2, 0
	mov	r2, 0
	cmovge	r2, r1
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_8:
	mov	r2, 0
	add	r1, sp, 14
	store_16	[r1], r2
	jmp _BB3_9
_BB3_9:
	add	r1, sp, 14
	load_16	r1, [r1]
	add	sp, sp, 16
	ret
.Lfunc_end3:
	.size	do_calc, .Lfunc_end3-do_calc
                                        // -- End function
	.globl	main                            // -- Begin function main
	.type	main,@function
main:                                   // @main
// %bb.0:
	sub	sp, sp, 24
	mov	r2, 0
	add	r1, sp, 20
	store_16	[r1], r2
	or	r1, r1, 2
	store_16	[r1], r2
	add	r1, sp, 18
	store_16	[r1], r2
	mov	r2, 1
	add	r1, sp, 17
	store_8	[r1], r2
	jmp _BB4_1
_BB4_1:                                 // =>This Inner Loop Header: Depth=1
	call	input
	mov	r2, r1
	add	r1, sp, 14
	store_16	[r1], r2
	load_16	r1, [r1]
	cmp	r1, 32
	je	_BB4_36
	jmp _BB4_2
_BB4_2:                                 //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 17
	load_8	r1, [r1]
	and	r1, r1, 255
	cmp	r1, 0
	je	_BB4_35
	jmp _BB4_3
_BB4_3:                                 //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 48
	jl	_BB4_6
	jmp _BB4_4
_BB4_4:                                 //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 57
	jg	_BB4_6
	jmp _BB4_5
_BB4_5:                                 //   in Loop: Header=BB4_1 Depth=1
	load_16	r1, [stack]
	add	r3, sp, 18
	load_16	r2, [r3]
	lsl	r2, r2, 3
	add	r1, r1, r2
	mov	r2, 1
	store_8	[r1], r2
	add	r1, sp, 14
	load_16	r1, [r1]
	add	r2, r1, 65488
	load_16	r1, [stack]
	load_16	r3, [r3]
	lsl	r3, r3, 3
	add	r1, r1, r3
	add	r1, r1, 4
	store_16	[r1], r2
	jmp _BB4_34
_BB4_6:                                 //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	call	is_op
	cmp	r1, 0
	je	_BB4_33
	jmp _BB4_7
_BB4_7:                                 //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 43
	jne	_BB4_9
	jmp _BB4_8
_BB4_8:                                 //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	store_16	[r1], r2
	jmp _BB4_27
_BB4_9:                                 //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 45
	jne	_BB4_11
	jmp _BB4_10
_BB4_10:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	mov	r2, 1
	store_16	[r1], r2
	jmp _BB4_26
_BB4_11:                                //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 124
	jne	_BB4_13
	jmp _BB4_12
_BB4_12:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	mov	r2, 2
	store_16	[r1], r2
	jmp _BB4_25
_BB4_13:                                //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 38
	jne	_BB4_15
	jmp _BB4_14
_BB4_14:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	store_16	[r1], r2
	jmp _BB4_24
_BB4_15:                                //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 94
	jne	_BB4_17
	jmp _BB4_16
_BB4_16:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	mov	r2, 4
	store_16	[r1], r2
	jmp _BB4_23
_BB4_17:                                //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 60
	jne	_BB4_19
	jmp _BB4_18
_BB4_18:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	mov	r2, 5
	store_16	[r1], r2
	call	input
	jmp _BB4_22
_BB4_19:                                //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 14
	load_16	r1, [r1]
	cmp	r1, 62
	jne	_BB4_21
	jmp _BB4_20
_BB4_20:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 8
	store_16	[r1], r2
	or	r1, r1, 2
	mov	r2, 6
	store_16	[r1], r2
	call	input
	jmp _BB4_21
_BB4_21:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_22
_BB4_22:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_23
_BB4_23:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_24
_BB4_24:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_25
_BB4_25:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_26
_BB4_26:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_27
_BB4_27:                                //   in Loop: Header=BB4_1 Depth=1
	load_16	r2, [stack]
	add	r1, sp, 18
	load_16	r3, [r1]
	lsl	r3, r3, 3
	add	r2, r2, r3
	mov	r3, 0
	store_8	[r2], r3
	add	r2, sp, 8
	load_16	r3, [r2]
	or	r2, r2, 2
	load_16	r5, [r2]
	load_16	r2, [stack]
	load_16	r4, [r1]
	lsl	r4, r4, 3
	add	r4, r2, r4
	add	r2, r4, 4
	add	r4, r4, 6
	store_16	[r4], r5
	store_16	[r2], r3
	load_16	r1, [r1]
	cmp	r1, 2
	jl	_BB4_32
	jmp _BB4_28
_BB4_28:                                //   in Loop: Header=BB4_1 Depth=1
	load_16	r2, [stack]
	add	r1, sp, 18
	load_16	r1, [r1]
	lsl	r1, r1, 3
	add	r1, r1, r2
	add	r1, r1, 65520
	load_8	r1, [r1]
	lsl	r1, r1, 8
	asr	r2, r1, 15
	asr	r1, r1, 8
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB4_31
	jmp _BB4_29
_BB4_29:                                //   in Loop: Header=BB4_1 Depth=1
	load_16	r2, [stack]
	add	r1, sp, 18
	load_16	r1, [r1]
	lsl	r1, r1, 3
	add	r1, r1, r2
	add	r1, r1, 65520
	load_8	r1, [r1]
	lsl	r1, r1, 8
	asr	r2, r1, 15
	asr	r1, r1, 8
	or	r1, r1, r2
	cmp	r1, 0
	je	_BB4_31
	jmp _BB4_30
_BB4_30:                                //   in Loop: Header=BB4_1 Depth=1
	load_16	r1, [stack]
	add	r2, sp, 18
	add	r13, sp, 4
	store_16	[r13], r2
	load_16	r2, [r2]
	lsl	r2, r2, 3
	add	r4, r1, r2
	add	r1, r4, 4
	add	r2, r4, 6
	load_16	r2, [r2]
	load_16	r1, [r1]
	add	r3, r4, 65524
	load_16	r3, [r3]
	add	r4, r4, 65532
	load_16	r4, [r4]
	call	do_calc
	mov	r2, r1
	add	r1, sp, 6
	add	r13, sp, 2
	store_16	[r13], r1
	store_16	[r1], r2
	load_16	r1, [r1]
	call	output
	add	r13, sp, 2
	load_16	r2, [r13]
	add	r13, sp, 4
	load_16	r1, [r13]
	load_16	r3, [r2]
	load_16	r4, [stack]
	load_16	r2, [r1]
	lsl	r2, r2, 3
	add	r2, r2, r4
	add	r2, r2, 65524
	store_16	[r2], r3
	load_16	r2, [r1]
	add	r2, r2, 65534
	store_16	[r1], r2
	jmp _BB4_31
_BB4_31:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_32
_BB4_32:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_33
_BB4_33:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_34
_BB4_34:                                //   in Loop: Header=BB4_1 Depth=1
	add	r1, sp, 18
	load_16	r2, [r1]
	add	r2, r2, 1
	store_16	[r1], r2
	jmp _BB4_35
_BB4_35:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 0
	add	r1, sp, 17
	store_8	[r1], r2
	jmp _BB4_37
_BB4_36:                                //   in Loop: Header=BB4_1 Depth=1
	mov	r2, 1
	add	r1, sp, 17
	store_8	[r1], r2
	jmp _BB4_37
_BB4_37:                                //   in Loop: Header=BB4_1 Depth=1
	jmp _BB4_1
.Lfunc_end4:
	.size	main, .Lfunc_end4-main
                                        // -- End function
	.ident	"clang version 20.1.7"
	.section	".note.GNU-stack","",@progbits
