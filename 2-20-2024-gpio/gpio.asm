	.export init_gpio

SYSCTL_RCGCGPIO_R	.field	0x400FE608
GPIO_PORTF_DIR_R	.field  0x40025400
GPIO_PORTF_AFSEL_R	.field  0x40025420
GPIO_PORTF_PUR_R	.field  0x40025510
GPIO_PORTF_DEN_R	.field  0x4002551C

; ---- init_gpio ----
init_gpio .asmfunc

	; SYSCTL_RCGCGPIO_R	.field	0x400FE608  <-- 0x20 for port f
	ldr r0, SYSCTL_RCGCGPIO_R
	;ldr r1, [r0]
	mov r1, #0x20
	str r1, [r0]

	nop
	nop

	; GPIO_PORTF_DEN_R	.field  0x4002551C <-- 0x1F
	ldr r0, GPIO_PORTF_DEN_R
	mov r1, #0x1F
	str r1, [r0]

	; GPIO_PORTF_DIR_R	.field  0x40025400 <-- 0x0E (01110)
	ldr r0, GPIO_PORTF_DIR_R
	mov r1, #0xE
	str r1, [r0]

	; GPIO_PORTF_PUR_R	.field  0x40025510 <-- 0x11 (10001)
	ldr r0, GPIO_PORTF_PUR_R
	mov r1, #0x11
	str r1, [r0]

	; GPIO_PORTF_AFSEL_R	.field  0x40025420 <-- 0x00000000 (=0)
	ldr r0, GPIO_PORTF_AFSEL_R
	mov r1, #0
	str r1, [r0]

	bx lr
	.endasmfunc
