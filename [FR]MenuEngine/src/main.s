.gba
.thumb
.open "./BPRE0.gba","./multi.gba", 0x08000000
.loadtable "./charmap.txt"

.org 0x806F282
.thumb
.align 2
LDR r0, =switch_menu|1
BX r0
.pool

.org 0x08810000
.importobj "./build/linked.o"

;super   equ 0x030030F0
choicex equ 0x0203ADE4

switch_menu:
	LDR r0, =hijack|1 ;C code
	BL goto_r0
	CMP r0, #0 ;hijack returns 1 if the input has been handled, 0 otherwise.
	BEQ handle_input_normally
goto_0806F358:
	LDR r0, =0x0806F358|1
	BX r0

handle_input_normally:
	LDR r0, =super
	LDRH r1, [r0, 0x2E]
	LDR r0, =0x40
	AND r0, r1
	CMP r0, #0
	BEQ goto_0806F2D2
	LDR r0, =0x0806F28E|1
	BX r0

goto_0806F2D2:
	LDR r0, =0x0806F2D2|1
goto_r0:
	BX r0

.align 2
menu_text:
.string 0x00,"Menu option\nDue",0xFF

.pool

.close
