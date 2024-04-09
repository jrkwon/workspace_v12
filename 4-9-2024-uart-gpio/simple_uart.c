//PROVIDED FUNCTIONS.  NO NEED TO MODIFY
#include <simple_uart.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"


//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the lab is running.
//
//*****************************************************************************
void InitConsole(void)
{
    // Enable GPIO port A which is used for UART0 pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for UART0 functions on port A0 and A1.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // Enable UART0 so that we can configure the clock.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);


        // Select the alternate (UART) function for these pins.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Initialize the UART for console I/O. 9600 BAUD
    UARTStdioConfig(0, 9600, 16000000);
}

//*****************************************************************************
//
// This function configures the ADC0 Peripheral for EE383LABS 4 and 5
// Configuration:
//  ADC0, Sequence 1(4 Samples)
//
//*****************************************************************************
void ADCInit(void)
{
    //Enable PORTE for analog input
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
     while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
         ;

     //Configure PORTE pins for analog input
     //PE1 analog input  CH2
     GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

     // The ADC0 peripheral must be enabled for use.
     SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
     while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
         ;

     // Enable sample sequence 1 with a processor signal trigger.  Sequence 1
     // will do a four samples when the processor sends a singal to start the
     // conversion.  Each ADC module has 4 programmable sequences, sequence 0
     // to sequence 3.  This lab is arbitrarily using sequence 1.
     ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);

     // Configure  ADC0 on sequence 1.  Sample the temperature sensor
     // (ADC_CTL_TS) and configure the interrupt flag (ADC_CTL_IE) to be set
     // when the sample is done.  Tell the ADC logic that this is the last
     // conversion on sequence 3 (ADC_CTL_END).  Sequence 1 has 4
     // programmable steps.  Sequence 1 and 2 have 4 steps, and sequence 0 has
     // 8 programmable steps. Sequence3 has 1 step. For more information on the
     // ADC sequences and steps, reference the datasheet.

     ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
     ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
     ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
     ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

 //    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH2);
 //    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH2);
 //    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2);
 //    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH2|ADC_CTL_IE|ADC_CTL_END);

     // Since sample sequence 1 is now configured, it must be enabled.
     ADCSequenceEnable(ADC0_BASE, 1);

     // Clear the interrupt status flag.  This is done to make sure the
     // interrupt flag is cleared before we sample.
     ADCIntClear(ADC0_BASE, 1);
}

//*****************************************************************************
//
// This function read a character from UART0
//
//*****************************************************************************
char CharGetUART0(void)
{
    return UARTCharGetNonBlocking (UART0_BASE);
}
