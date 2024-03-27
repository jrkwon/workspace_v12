	.export turn_on_blue_led
	.export turn_off_blue_led
	.export turn_on_red_led
	.export turn_off_red_led

LED_RED				.equ    0x2
LED_GREEN			.equ    0x8
LED_BLUE			.equ    0x4

GPIO_PORTF_DATA_R	.field  0x400253FC

; ---- turn_on_blue_led
turn_on_blue_led .asmfunc

	ldr r0, GPIO_PORTF_DATA_R
	; ldr r1, [r0]
	mov r1, #LED_BLUE
	str r1, [r0]

	bx lr
	.endasmfunc


; ---- turn_on_blue_led
turn_off_blue_led .asmfunc

	ldr r0, GPIO_PORTF_DATA_R
	; ldr r1, [r0]
	mov r1, #0
	str r1, [r0]

	bx lr
	.endasmfunc


; ---- turn_on_blue_led
turn_on_red_led .asmfunc

	ldr r0, GPIO_PORTF_DATA_R
	; ldr r1, [r0]
	mov r1, #LED_RED
	str r1, [r0]

	bx lr
	.endasmfunc


; ---- turn_on_blue_led
turn_off_red_led .asmfunc

	ldr r0, GPIO_PORTF_DATA_R
	; ldr r1, [r0]
	mov r1, #0
	str r1, [r0]

	bx lr
	.endasmfunc

