.thumb
.align 2

MOD:
PUSH {lr}
SWI 0x6
MOV r0, r1
POP {r1}
BX r1
