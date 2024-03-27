/*
 * gpio_port_f.c
 *
 *  Created on: Mar 19, 2024
 *      Author: jaerock
 */
#include "gpio_port_f.h"


void init_gpio_port_f(void)
{
    int foo;

    /* --
    LDR R1, SYSCTL_RCGCGPIO_R       ; 1) activate clock for Port F
    LDR R0, [R1]
    ORR R0, R0, #0x20               ; set bit 5 to turn on clock
    STR R0, [R1]
    -- */
    /* activate clock for port F */
    SYSCTL_RCGCGPIO_R |= 0x20;
    foo = 1; /* to mimic two NOPs */
    /* --
    LDR R1, GPIO_PORTF_LOCK_R       ; 2) unlock the lock register
    LDR R0, GPIO_LOCK_KEY             ; unlock GPIO Port F Commit Register
    STR R0, [R1]
    -- */
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    /* --
    LDR R1, GPIO_PORTF_CR_R         ; enable commit for Port F
    MOV R0, #0xFF                   ; 1 means allow access
    STR R0, [R1]
    -- */
    GPIO_PORTF_CR_R = 0xFF;
    /* --
    LDR R1, GPIO_PORTF_AMSEL_R      ; 3) disable analog functionality
    MOV R0, #0                      ; 0 means analog is off
    STR R0, [R1]
    -- */
    GPIO_PORTF_AMSEL_R = 0;
    /* --
    LDR R1, GPIO_PORTF_PCTL_R       ; 4) configure as GPIO
    MOV R0, #0x00000000             ; 0 means configure Port F as GPIO
    STR R0, [R1]
    -- */
    GPIO_PORTF_PCTL_R = 0;
    /* ---
    LDR R1, GPIO_PORTF_DIR_R        ; 5) set direction register
    MOV R0,#0x0E                    ; PF0 and PF4 input, PF3-1 output
    STR R0, [R1]
    -- */
    GPIO_PORTF_DIR_R = 0x0E;
    /* --
    LDR R1, GPIO_PORTF_AFSEL_R      ; 6) regular port function
    MOV R0, #0                      ; 0 means disable alternate function
    STR R0, [R1]
    -- */
    GPIO_PORTF_AFSEL_R = 0;
    /* --
    LDR R1, GPIO_PORTF_PUR_R        ; pull-up resistors for PF4,PF0
    MOV R0, #0x11                   ; enable weak pull-up on PF0 and PF4
    STR R0, [R1]
    -- */
    GPIO_PORTF_PUR_R = 0x11;
    /* --
    LDR R1, GPIO_PORTF_DEN_R        ; 7) enable Port F digital port
    MOV R0, #0xFF                   ; 1 means enable digital I/O
    STR R0, [R1]
    -- */
    GPIO_PORTF_DEN_R = 0x1F;
}





