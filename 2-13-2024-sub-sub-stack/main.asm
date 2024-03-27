; nested subroutine example

	.text

	.global main

main:
	bl sub1
	mov r1, #10

loop:
	b loop


; ---- sub1 ---
sub1:
	mov r0, #20
	push {lr}
	bl sub2
	pop {lr}
	bx lr

; --- sub2 ---
sub2:
	mov r2, #0x124
	push {lr}
	bl sub3
	mov r2, #0x124
	mov r2, #0x124
	mov r2, #0x124
	mov r2, #0x124
	pop {lr}
	mov r2, #0x124
	mov r2, #0x124
	mov r2, #0x124
	bx lr

; --- sub3 ---
sub3:
	mov r3, #12
	bx lr
