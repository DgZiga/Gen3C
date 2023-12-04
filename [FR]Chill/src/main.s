.gba
.thumb
.open "./BPRE0.gba","./multi.gba", 0x08000000

.org 0x0803ED76 ;insert hijack when spatk is used. r6 contains battle_data
.thumb
.align 2
LDR r3, =halve_spatk_when_chill|1
BX r3
.pool
;override lasts until 0x0803ED80(ecluded)


.org 0x0801950A ;always thaw out
.thumb
.align 2
;just changing r4 to 0 would thaw the pkmn out, but its not enough and we need to actually skip the animations and everything else
LDR r0, =0x08019BD4|1
BX r0
.pool

.org 0x08018552 ;1/16th damage if frozen. r0 contains the status
.thumb
.align 2
;just changing r4 to 0 would thaw the pkmn out, but its not enough and we need to actually skip the animations and everything else
LDR r1, =chip_damage_when_chill|1
BX r1
.pool
;override lasts until 0x0801855A(ecluded)


.org 0x08810000 ;Freeespace
.thumb
.align 2

halve_spatk_when_chill:
	LDRH r3, [R6,#8] ;original 0803ED76, load spatk
	PUSH {r0-r1}
	MOV r1, #0x4C ;battle_data.status1
	LDR r0, [r6, r1]
	MOV r1, #0x20 ;freeze
	CMP r0, r1
	BNE halve_spatk_when_chill_back_to_normal
	LSR r3, #0x1
	B halve_spatk_when_chill_back_to_normal

/*
original:
ROM:0803ED76    LDRH    R3, [R6,#battle_data_t.stats+6] @ spatk ALREADY IN BEGINNING OF halve_spatk_when_chill
ROM:0803ED78    MOV     R8, R3
ROM:0803ED7A    LDR     R0, [SP,#0x4C+battle_data_defender]
ROM:0803ED7C    LDRH    R0, [R0,#battle_data_t.stats+8]
ROM:0803ED7E    STR     R0, [SP,#0x4C+var_34]
*/
halve_spatk_when_chill_back_to_normal:
	POP {r0-r1}
	MOV r8, r3
	LDR r0, [SP, #0x4]
	LDRH r0, [R0, #0xA]
	STR r0, [SP,#0x18]
	LDR r1, =0x0803ED80|1
	BX r1
	





chip_damage_when_chill:
	MOV r1, #0x20
	CMP r0, r1
	BEQ chip_damage_when_chill_apply_dmg
	B chip_damage_when_chill_back_to_normal

chip_damage_when_chill_apply_dmg:
	LDR r1, =0x0801855C|1
	BX r1

/*
original:
ROM:08018552                 MOVS    R1, #0x10
ROM:08018554                 ANDS    R0, R1
ROM:08018556                 CMP     R0, #0
ROM:08018558                 BNE     loc_801855C
ROM:0801855A                 B       loc_8018C12
 */
chip_damage_when_chill_back_to_normal:
	mov r1, #0x10
	and r0, r1
	cmp r0, #0
	bne chip_damage_when_chill_apply_dmg
	ldr r0, =0x8018C12|1
	bx r0


.pool

.close