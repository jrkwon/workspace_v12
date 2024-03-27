/*
 * util.c
 *
 *  Created on: Mar 19, 2024
 *      Author: jaerock
 */
#include "util.h"

void delay(void)
{
    unsigned long n = 0xFFFFF;

    while(n--)
        ;
}

void delay_short(void)
{
    unsigned long n = 0xFFFF;

    while(n--)
        ;
}


void init_gpio(void)
{
    init_gpio_port_f();
}


