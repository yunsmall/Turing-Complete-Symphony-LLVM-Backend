



put:                                    // @put
// %bb.0:
	sub	sp, sp, 4
	mov	r3, r2
                                        // kill: def $r2 killed $r1
	add	r2, sp, 3
	store_8	[r2], r1
	add	r1, sp, 1
	store_16	[r1], r3
	load_8	r2, [r2]
	load_16	r1, [r1]
	store_8	[r1], r2
	add	sp, sp, 4
	ret


                                        // -- End function


show:                                   // @show
// %bb.0:
	sub	sp, sp, 10
	mov	r2, r1
                                        // kill: def $r1 killed $r2
	add	r1, sp, 9
	store_8	[r1], r2
	mov	r3, 32768
	add	r2, sp, 7
	mov	r13, sp
	store_16	[r13], r2
	store_16	[r2], r3
	load_16	r2, [r2]
	load_16	r3, [r2]
	add	r2, sp, 5
	store_16	[r2], r3
	load_16	r2, [r2]
	add	r3, r2, 32770
	add	r2, sp, 3
	store_16	[r2], r3
	load_8	r1, [r1]
	and	r1, r1, 255
	load_16	r2, [r2]
	call	put
	mov	r13, sp
	load_16	r1, [r13]
	load_16	r1, [r1]
	load_16	r2, [r1]
	add	r2, r2, 1
	store_16	[r1], r2
	add	sp, sp, 10
	ret


                                        // -- End function


show_num:                               // @show_num
// %bb.0:
	sub	sp, sp, 4
	mov	r2, r1
                                        // kill: def $r1 killed $r2
	add	r1, sp, 3
	mov	r13, sp
	store_16	[r13], r1
	store_8	[r1], r2
	load_8	r1, [r1]
	and	r1, r1, 255
	udiv	r1, r1, 100
	or	r1, r1, 48
	call	show
	mov	r13, sp
	load_16	r1, [r13]
	load_8	r1, [r1]
	and	r1, r1, 255
	urem	r1, r1, 100
	udiv	r1, r1, 10
	or	r1, r1, 48
	call	show
	mov	r13, sp
	load_16	r1, [r13]
	load_8	r1, [r1]
	and	r1, r1, 255
	urem	r1, r1, 10
	or	r1, r1, 48
	call	show
	add	sp, sp, 4
	ret


                                        // -- End function


test:                                   // @test
// %bb.0:
	mov	r1, 12
	call	show_num
	mov	r1, 123
	call	show_num
	ret


                                        // -- End function


