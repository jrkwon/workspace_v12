//****************** EE505lab3.c ***************
// Program written by: Your Names
// Date Created: 11/03/2013,  modified 2019
// Original Author: Chris Mitchell, Samir Rawashdeh  (University of Kentucky)
// Modified 2024 by Jaerock Kwon
//
// Brief description of the program:
// This lab demonstrates a simple enviornmental monitoring unit.  This
// program will read the internal analog temperature sensor on the TivaWare
// Launchpad development board through the onboard ADC.  The temperature will
// then be converted to Celsius and Farenheit and printed to the console.

//
// The following UART signals are configured only for displaying console
// messages for this example.  These are not required for operation of the
// ADC.
// - UART0 peripheral
// - GPIO Port A peripheral (for UART0 pins)
// - UART0RX - PA0
// - UART0TX - PA1
//
//
// NOTE: The internal temperature sensor is not calibrated.  This example
// just takes the raw temperature sensor sample and converts it using the
// equation found in the datasheet.
//
//*****************************************************************************


// system header files
#include <stdbool.h>
#include <stdint.h>
// TivaWare driver header
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
// TivaWare utilities
#include "utils/uartstdio.h"
// user header
#include "simple_uart.h"
#include "led.h"

//Determines the sample rate of the ADC
#define CLK_SCALE_VALUE     6

//****************************************************************************
//****************************************************************************
//Student Written Functions
uint32_t ConvertToFahrenheit(uint32_t TempC);  //To be completed
void PrintTemps(uint32_t TempC);//To be modified



//*****************************************************************************
//
// Configure ADC0 for the temperature sensor input with a single sample.  Once
// the sample is done, an interrupt flag will be set, and the data will be
// read then displayed on the console via UART0.
//
//*****************************************************************************
int main(void)
{
    //
    // This array is used for storing the data read from the ADC FIFO. It
    // must be as large as the FIFO for the sequencer in use.
    uint32_t ui32ADC0Value[4];

    // These variables are used to store the temperature conversions for
    // AVG, Celsius and Fahrenheit.
    uint32_t ui32TempAvg;
    uint32_t ui32TempValueC;
    char ch;


    // Set the clocking to run at 20 MHz (200 MHz / 5) using the PLL.  When
    // using the ADC, you must either use the PLL or supply a 16 MHz clock
    // source.
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ); //changed from SYSCTL_SYSDIV_10 (CM)

    // Set up the serial console to use for displaying messages.  This is just
    // for this lab program and is not needed for ADC operation.
    InitConsole();

    // Display the setup on the console.
    UARTprintf("AENG/ECE505 Lab 3: Introduction to C Programming and UART\n");
    UARTprintf("*****************************************************\n");
    UARTprintf("Analog Input: Internal Temperature Sensor\n");

    //Init the ADC
    ADCInit();
    // init gpio
    InitPortF();

    UARTprintf("Initialization Complete...\n");

    // Sample the temperature sensor forever.  Display the value on the
    // console.
    while(1)
    {
        // Trigger the ADC conversion.
        ADCProcessorTrigger(ADC0_BASE, 1);

        // Wait for conversion to be completed.
        while(!ADCIntStatus(ADC0_BASE, 1, false))
            ;

        // Clear the ADC interrupt flag.
        ADCIntClear(ADC0_BASE, 1);

        // Read ADC Values.
        ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);

        //Average the 4 Samples
        ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;

        //Convert Raw Data to Temp Celsius
        ui32TempValueC = (1475 - ((2475 * ui32TempAvg))/4096)/10;

        ch = CharGetUART0();
        if (ch == 'G' || ch == 'g')
        {
            UARTprintf("Toggling Green LED.\n", ch);
            ToggleLED(LED_GREEN);
        }
        if (ch == 'B' || ch == 'b')
        {
            UARTprintf("Toggling Blue LED.\n", ch);
            ToggleLED(LED_BLUE);
        }
        if (ch == 'R' || ch == 'r')
        {
            UARTprintf("Toggling Red LED.\n", ch);
            ToggleLED(LED_RED);
        }
        else if (ch == 'C' || ch == 'c') {
            // Display the temperature value on the console.
            PrintTemps (ui32TempValueC);
        }
        //else {
        //    UARTprintf("Unknown command: %c\n", ch);
        //}

        //
        // This function provides a means of generating a constant length
        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
        // 250ms arbitrarily.
        //
        SysCtlDelay(SysCtlClockGet()/CLK_SCALE_VALUE);
    }
}

//***************************************************************************
//NOTE: Fill/Modify in The Following Functions
//***************************************************************************

//This function converts the 32bit unsigned value representation of Celsius
//Temperature from the ADC and converts it to Farenheit
uint32_t ConvertToFahrenheit ( uint32_t TempC)
{
    //Fill out this function
    uint32_t TempF=0;



    return TempF;
}

//This function prints the two passed temperatures to the console in an
//easy human readable format.
void PrintTemps (uint32_t TempC)
{
    UARTprintf("Temperature = %3d*C\n", TempC);
}

//EOF


