.saturn
.include "ip/ip.s"
.create EXE_PATH, EntryPoint

.org EntryPoint
__entry:
	mov.l @@stack_pointer,r15
	mov.l @@main_func,r0
	jmp r0
	nop
	.align 4
	@@main_func:     .dd _ss_main
	@@stack_pointer: .dd EntryPoint

	.importobj BUILD_DIR + "/combined.a"
	.importobj LIBGCC_PATH
	.include "src/mem.s"
	
	_malloc: ;; Not implemented, but required by libgcc for some weird reason
	_free:
	_abort:
		bra _abort ;; Endless loop...
		nop
	
_bstart:

.close
