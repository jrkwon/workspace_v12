#include "led.h"
#include "util.h"
#include "sw.h"

/**
 * main.c
 */
void main(void)
{
    init_gpio();

    while(1) {
        blue_led_on();
        if (is_left_switch_pressed() == 1)
            delay_short();
        else
            delay();

        blue_led_off();
        if (is_left_switch_pressed() == 1)
            delay_short();
        else
            delay();
    }
}
