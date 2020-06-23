.thumb
.align 2

.equ VBlank_callback_addr, 		0x030030F0
.equ c_main_addr, 				0x08804021

.equ orig_addr_store_location, 	0xFFFFFFFF

MAIN:
PUSH {r0-r1, lr}

LDR r0, =VBlank_callback_addr
LDR r1, =orig_addr_store_location
LDR r0, [r0]
STR r0, [r1]

LDR r0, =VBlank_callback_addr
LDR r1, =c_main_addr
STR r1, [r0]

POP {r0-r1, pc}
