; if-then example

; ============= data section =================
	.data
Num	.word 	25599

; ============= code section =================
	.text
; ------------- addresses of variables -------
pNum .word Num

; ------------- code starts! -----------------
	.global main

main:
	bl change		; function call
	ldr r5, [r0]	; some dummy code
	bl change		; function call again

loop:
	b loop

; ------------- subroutine --------------------
change:
	ldr	r0, pNum
	ldr r1, [r0]		; r1 = 25,599
	cmp r1, #25600		; 25,600 --> 0x6400
	bhs skip			; bhs indicates unsigned number comparison
	add r1, #1			; r1 = Num + 1
	str	r1, [r0]

skip:
	bx lr				; return to the caller
