; gpio examples

	.import init_gpio
	.import turn_on_blue_led
	.import turn_off_blue_led
	.import turn_on_red_led
	.import turn_off_red_led
	.import wait

	.data

	.global main
	.text

; ----- main -------
main .asmfunc

	; this is a dummy line for starting a demo
	; mov r1, #0xdead
	bl init_gpio

loop:
	bl turn_on_blue_led
	; wait for a while
	bl wait
	bl turn_off_blue_led
	bl wait
	bl turn_on_red_led
	; wait for a while
	bl wait
	bl turn_off_red_led
	bl wait

	b loop

	.endasmfunc
; ------------------
