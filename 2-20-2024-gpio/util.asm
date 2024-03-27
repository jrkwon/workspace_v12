	.export wait

p_max_delay			.field  max_delay
max_delay			.field 0x004FFFFF

; --- wait for a while ---
wait .asmfunc

	;mov r0, #0xFFFF	    ; max number
	ldr r0, p_max_delay
	ldr r2, [r0]
	mov r1, #0			; counter
loop_wait:
	cmp r1, r2
	beq done
	add r1, #1
	b loop_wait

done:
	bx lr
	.endasmfunc
