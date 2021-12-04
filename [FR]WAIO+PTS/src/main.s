.gba
.thumb
.open "./BPRE0.gba","./multi.gba", 0x08000000


/* Hijack for WAIO (hijacks "step" routine) */
.org 0x0806D5F6
.thumb
.align 2
LDR r0, =MAIN_WAIO|1
BX r0
.pool


/* Hijack for PTS */
.org 0x0807759c
.thumb
.align 2
LDR r0, =EXEC_TASKS_AT_FREE_SPACE_ASM|1
BX r0
.pool




.org 0x08810000
.importobj "./build/linked.o"

/* WAIO stuff */

MAIN_WAIO:
PUSH {r0-r5}
LDR r3, =check_showsprite_every_step|1
BL CALL_USING_R3

END_WAIO:
POP {r0-r5}
/*Instructions from 0x806D5F6*/
LSL r0, r0, #0x18
LSR r0, r0, #0x18
CMP r0, #0x1
BEQ BRANCHER_WAIO
MOV r0, r5
MOV r1, r4
LDR r3, =0x0806DA11
BL CALL_USING_R3
LSL r0, r0, #0x18
LSR r0, r0, #0x18
CMP r0, #0x1
BEQ BRANCHER_WAIO
MOV r0, r4
LDR r0, =0x0806D611
BX r0

BRANCHER_WAIO:
LDR r0, =0x0806D651
BX r0

CALL_USING_R3:
BX r3

/* PTS stuff */
EXEC_TASKS_AT_FREE_SPACE_ASM:
PUSH {r0-r5}
LDR r3, =exec_tasks_at_free_space|1
BL CALL_USING_R3

END_PTS:
/* Back on track */
POP {r0-r5}
POP {r4, r5}
POP {r0}
BX r0

BX_R4:
BX r4

.pool


/* DEMO */
.org 0x08722000
.byte 0x00
.byte 0x01
.byte 0x00
.byte 0x05


.byte 0x00
.byte 0x04
.byte 0xFF
.byte 0x05


.byte 0x00
.byte 0x07
.byte 0xFF
.byte 0x05


.byte 0xFF
.byte 0xFF
.byte 0xFF
.byte 0x05


.byte 0xFF
.byte 0xFF

.close