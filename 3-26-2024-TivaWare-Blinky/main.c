//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2011-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.4.178 of the DK-TM4C123G Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED.
//
//*****************************************************************************

#define LED_COLOR_RED       GPIO_PIN_1
#define LED_COLOR_BLUE      GPIO_PIN_2
#define LED_COLOR_GREEN     GPIO_PIN_3

void InitPort(void)
{
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Enable the GPIO pin for the LED (PF1, PF2, PF3).
    // Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    // Enable the GPIO pin for the switches (SW1, SW2)
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
}

void Wait(void)
{
    volatile uint32_t ui32Loop;

    //
    // Delay for a bit.
    //
    for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
    {
    }
}

void TurnOnLED(uint32_t LEDColor)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LEDColor, LEDColor);
}

void TurnOffLED(uint32_t LEDColor)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LEDColor, 0);
}

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int main(void)
{
    uint32_t colors[] = {
       LED_COLOR_RED, LED_COLOR_GREEN, LED_COLOR_BLUE
    };
    uint8_t i;
    uint8_t size = sizeof(colors)/sizeof(colors[0]);

    InitPort();

    while(1)
    {
        for (i = 0; i < size; i++) {
            TurnOnLED(colors[i]);
            Wait();
            TurnOffLED(colors[i]);
            Wait();
        }
    }
}
