.thumb
.align 2

.equ c_main_addr, 	0x0880402D;
.equ original_exec, 0x0800FA41;

MAIN:
LDR r2, [SP, #0x10]
ADD r0, r2, r0
LDRH r1, [r4, #0x4]
LDRB r2, [r4, #0x2]
PUSH {r0-r1}
PUSH {r3-r7}
LDR r0, =c_main_addr
BL GOTO_R0
MOV r2, r0

RESUME_EXEC:
POP {r3-r7}
POP {r0-r1}
LDR r3, =original_exec //R3 will be immediately ovverwritten by the instruction at original_exec
BX r3

GOTO_R0:
BX r0

DIV:
SWI 0x6
BX LR
