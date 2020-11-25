.thumb
.align 2

.equ check_showsprite_every_step, 0x088067E5

MAIN:
PUSH {r0-r5}
LDR r3, =check_showsprite_every_step
BL CALL_USING_R3

END:
POP {r0-r5}
/*Instructions from 0x806D5F6*/
LSL r0, r0, #0x18
LSR r0, r0, #0x18
CMP r0, #0x1
BEQ BRANCHER
MOV r0, r5
MOV r1, r4
LDR r3, =0x0806DA11
BL CALL_USING_R3
LSL r0, r0, #0x18
LSR r0, r0, #0x18
CMP r0, #0x1
BEQ BRANCHER
MOV r0, r4
LDR r0, =0x0806D611
BX r0

BRANCHER:
LDR r0, =0x0806D651
BX r0

CALL_USING_R3:
BX r3
