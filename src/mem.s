memset:
_memset:
	mov		r4, r0
	add		r6, r0
	add		#-1, r0
	@@loop:
		mov.b	r5, @-r0
		cmp/hs	r0, r4
		bf		@@loop
	rts
	mov		r4, r0
_memset_w:
	mov		r4, r0
	add		r6, r0
	add		#-2, r0
	@@loop:
		mov.w	r5, @-r0
		cmp/hs	r0, r4
		bf		@@loop
	rts
	mov		r4, r0
_memset_l:
	mov		r4, r0
	add		r6, r0
	add		#-4, r0
	@@loop:
		mov.l	r5, @-r0
		cmp/hs	r0, r4
		bf		@@loop
	rts
	mov		r4, r0

memcpy:
_memcpy:
	mov		r4, r2
	mov		r6, r0
	@@loop:
		mov.b	@r5+, r1
		mov.b	r1, @r4
		add		#-1, r0
		add		#1, r4
		cmp/eq	#0, r0
		bf		@@loop
	rts
	mov		r2, r0
	