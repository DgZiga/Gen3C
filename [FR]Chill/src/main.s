.gba
.thumb
.open "./BPRE0.gba","./multi.gba", 0x08000000

.org 0x0803F3D0 ;insert hijack when spatk is used. r6 contains battle_data, r8 contains the spatk
.thumb
.align 2
LDR r0, =halve_spatk_when_chill|1
BX r0
.pool
;override lasts until 0x0803F3D8(ecluded)


.org 0x0801950A ;always thaw out
.thumb
.align 2
;just changing r4 to 0 would thaw the pkmn out, but its not enough and we need to actually skip the animations and everything else
LDR r0, =0x08019BD4|1
BX r0
.pool

.org 0x08810000 ;Freeespace
.thumb
.align 2

halve_spatk_when_chill:
	PUSH {r1}
	MOV r1, #0x4C ;battle_data.status1
	LDR r0, [r6, r1]
	MOV r1, #0x20 ;freeze
	CMP r0, r1
	BNE halve_spatk_when_chill_back_to_normal
	mov r5, r8
	LSR r5, #0x1
	mov r8, r5
	B halve_spatk_when_chill_back_to_normal

/*
original:
ROM:0803F3D0                 MOV     R5, R8
ROM:0803F3D2                 MULS    R5, R1
ROM:0803F3D4                 ADDS    R2, #1
ROM:0803F3D6                 ADDS    R0, R0, R2
ROM:0803F3D8                 LDRB    R1, [R0]
*/
halve_spatk_when_chill_back_to_normal:
	POP {r1}
	mov r5, r8
	MUL r5, r1
	ADD r2, #1
	ADD r0, r2
	LDRB r1, [r0]
	LDR r0, =0x0803F3DA|1
	BX r0
	

.pool

.close