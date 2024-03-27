; example 3.4 variables example

; ==================================
; data section
; ==================================
	.data
N	.word	13		; decimal 13. 0x0000000D
M	.word	0		;

; ==================================
; code section
; ==================================
	.text
; -------- addresses to the variables --------
pN	.word	N
pM	.word   M

; -------- code start ---------

	.global main

main:

	;ldr r0, =N
	; load from N
	ldr r0, pN		; r0 will have N's address
	ldr r1, [r0]	; r1 <-- the value of N ; r1 should be 0x0D

	add r2, r1, #10	; r2 <-- r1 + 10	; r2 should be 0x17

	; save it to M
	;ldr r3, =M
	ldr r3, pM
	str r2, [r3]

loop:
	b loop
