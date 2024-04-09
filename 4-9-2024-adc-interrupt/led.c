/*
 * led.c
 *
 *  Created on: Apr 9, 2024
 *      Author: jaerock
 */

// system header files
#include <stdbool.h>
#include <stdint.h>
// TivaWare driver header
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
// user headers
#include "led.h"

void InitPortF(void)
{
    /***********************
    * Setup PORTF for GPIO *
    ***********************/
    //Enable PORTF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);  //Enable clock on GPIO PORTF
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);  //Sets pins 1,2,3 as outputs

    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
}

void ToggleLED(uint32_t led_type)
{
    uint32_t led_status;

    led_status = GPIOPinRead(GPIO_PORTF_BASE, led_type);  //read current state of green LED

    if (led_status){
        GPIOPinWrite(GPIO_PORTF_BASE, led_type, 0x00);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, led_type, led_type);
    }
}

/* -------------
void ToggleGreenLED(void)
{
    int32_t  led;

    led = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3);  //read current state of green LED

    if (led){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    }
}

void ToggleBlueLED(void)
{
    int32_t  led;

    led = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2);  //read current state of blue LED

    if (led){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }
}

void ToggleRedLED(void)
{
    int32_t  led;

    led = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);  //read current state of red LED

    if (led){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    }
}
 --------- */

