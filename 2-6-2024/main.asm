        ; data section
        .data
var1:   .field  0x000000AA


        ; code section
        .text
        .global main


main:

        ldr r0, p_var1
        ldr r1, [r0]
        and r1, r1, #0x7E
        str r1, [r0]        ; var1 --> 2A

loop:   b loop         ;


p_var1: .field     var1, 32

