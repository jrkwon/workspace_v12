/*
 * led.c
 *
 *  Created on: Mar 19, 2024
 *      Author: jaerock
 */
#include "gpio_port_f.h"

/* bit-banding */
#define PF1                 (*((unsigned long *)0x40025008))
#define PF2                 (*((unsigned long *)0x40025010))
#define PF3                 (*((unsigned long *)0x40025020))

#define RED                 0x02
#define BLUE                0x04
#define GREEN               0x08

void blue_led_on(void)
{
   /* --
    LDR R1, PF2
    MOV R0, #BLUE                   ; R0 = BLUE (blue LED on)
    STR R0, [R1]                    ; turn the blue LED on
    -- */
    PF2 = BLUE;
}

void red_led_on(void)
{
    GPIO_PORTF_DATA_R |= RED;
    /* PF1 = RED; */ /* bit-banding */
}

void red_led_off(void)
{
    GPIO_PORTF_DATA_R &= ~RED;  /* RED: 0000 0010 --> ~RED: 1111 1101  -->   1100 1111 & ~RED ==> 1100 1101 */
}

void blue_led_off(void)
{
    /* --
    LDR R1, PF2
        MOV R0, #0                      ; R0 = 0
        STR R0, [R1]                    ; turn the blue LED OFF
     -- */
    PF2 = 0;
}



