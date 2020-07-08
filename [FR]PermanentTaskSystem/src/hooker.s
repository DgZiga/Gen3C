.thumb
.align 2

.equ free_space_start, 0x0202F0F4;

EXEC_TASKS_AT_FREE_SPACE:
PUSH {r1}
LDR r1, =free_space_start
MOV r0, #0

LOOP:
CMP r0, #5
BEQ END
LDR r4, [r1]
CMP r4, #0
BEQ CONTINUE
PUSH {r0, r1, r4}
BL BX_R4
POP {r0, r1, r4}

CONTINUE:
ADD r1, #0x20
ADD r0, #1
B LOOP

END:
POP {r1}
/* Back on track */
POP {r4, r5}
POP {r0}
BX r0

BX_R4:
BX r4
