; this is my first time ever demo
		.global main


main:
		MOV R0, #0x03
		MOV R1, #0xf0
		AND R2, R0, #0xF0

		ADD R2, R1, R0   	; R2(0xF3) = R1(0xF0) + R0(0x03)


loop:	B loop

