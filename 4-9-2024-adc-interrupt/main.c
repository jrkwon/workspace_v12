#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib/systick.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/interrupt.h"

#include "led.h"


// LED pins
#define LED_RED         GPIO_PIN_1
#define LED_BLUE        GPIO_PIN_2
#define LED_GREEN       GPIO_PIN_3
// SW pins
#define SW1             GPIO_PIN_4
#define SW2             GPIO_PIN_0

//*****************************************************************************
// Function Prototypes

// interrupt handlers
void SwitchInterruptHandler(void);
// (2-1) Add your interrupt handler function prototype here.
// TO DO:
void MyPreciousSystickHandler(void);


// system initialization
void InitBoard(void);
void InitSystickTimer(void);

// utilities
void PrintTemps(uint32_t TempC);

// functions are given - no need to change
void InitConsole(void);
void ADCInit(void);
void TurnOffLED(void);


//*****************************************************************************
// Global variables
// Use this variable to count how many times the Systick timer is called
uint32_t systick_counter = 0;
// Use this variable to count how many seconds have passed since the Systick
// timer started.
uint32_t seconds = 0;
//Determines the sample rate of the ADC
uint32_t clkscalevalue = 6;

//*****************************************************************************
//
// Interrupt Handlers
//
//*****************************************************************************

// (2-1) Yout Systick ISR
// TO DO:
void MyPreciousSystickHandler(void)
{
    // this function will be called every 1ms
    systick_counter++; // ms passed after the interrupt is enabled
    if (systick_counter == 1000) {
        seconds++;
        systick_counter = 0;
    }
    // another ways for your information
    /*if (systick_counter%1000 == 0) {
        seconds++;
    }*/

}


void SwitchInterruptHandler(void)
{
    uint32_t int_status;
    //unsigned char led_status;
    uint32_t led;

    // (3-2)
    // TO DO:
    // Acknowledge the flag

    int_status = GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, int_status);

    if(int_status == SW1) {
        // turn off the other color LED if that is on
        GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, 0);
        led = LED_BLUE;
    }
    else if(int_status == SW2) {
        // turn off the other color LED if that is on
        GPIOPinWrite(GPIO_PORTF_BASE, LED_BLUE, 0);
        led = LED_GREEN;
    }

    // (3-3) Toggle LED light
    // TDO DO:
    ToggleLED(led);
}

//*****************************************************************************
//
// This function sets up Systick timer
//
//*****************************************************************************
void InitSystickTimer(void)
{
    // SysTick timer initialization
    SysTickEnable();
    // (2-1) Set up the Systcik timer to generate interrupt request every 1ms
    //     Note that your system's clock cycle is configured at 80MHz.
    //     Hint: SysCtlClockGet() will return 80,000,000
    // TO DO:
    SysTickPeriodSet(SysCtlClockGet()/1000); // 1ms

    // (2-3) Register your interrupt handler for Systick interrupt
    // TO DO:
    SysTickIntRegister(MyPreciousSystickHandler);

    // Enable Systick interrupt
    SysTickIntEnable();

}

//*****************************************************************************
//
// This function sets up GPIO, Interrupt
//
//*****************************************************************************
void InitBoard(void)
{
    // System clock initialization
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    // GPIO initialization
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//ENABLE PORT F
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
            ;

    /* Set CR manually to allow changes to PF4-0 */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = LED_RED|LED_BLUE|LED_GREEN|SW1|SW2;

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_BLUE|LED_RED|LED_GREEN); //RED AND BLUE LED AS OUTPUTS
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW1|SW2);//SWITCH AS INPUT
    GPIOPadConfigSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); //WEAK PULL UP FOR SWITCH

    // (3-1) GPIO interrupt initialization for push button
    // TO DO:
    GPIOIntTypeSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_RISING_EDGE);//TRIGGER INTERRUPT ON RISING EDGE
    GPIOIntRegister(GPIO_PORTF_BASE, SwitchInterruptHandler);// REGISTER SWITCH INTERRUPT
    GPIOIntEnable(GPIO_PORTF_BASE, SW1|SW2); // ENABLE INTERRUPTS ON THE SWITCH
}

//*****************************************************************************
//
// Utility function
//
//*****************************************************************************
//This function prints the two passed temperatures to the console in an
//easy human readable format.
void PrintTemps (uint32_t TempC)
{
    UARTprintf("Temperature = %3d*C\n", TempC);
}

// (2-4) PrintTempsWithTime
// TO DO:
void PrintTempsWithTime (uint32_t TempC)
{
    // mm:ss:mss  to enforce 00:01:012 instead of 0:1:12
    UARTprintf("%02d:%02d:%03d,%d\n", seconds/60, seconds, systick_counter, TempC);
}

//*****************************************************************************
//
// main
//
//*****************************************************************************

int main(void)
{
    // local variables to Main
    // This array is used for storing the data read from the ADC FIFO. It
    // must be as large as the FIFO for the sequencer in use.
    uint32_t ui32ADC0Value[4];

    // These variables are used to store the temperature conversions for
    // AVG, Celsius and Fahrenheit.
    uint32_t ui32TempAvg;
    uint32_t ui32TempValueC;

    InitBoard();
    InitSystickTimer();

    // UART initialization
    InitConsole();

    // Display the setup on the console.
    UARTprintf("ECE/AENG 505 Exp4: ADC and Interrupts\n");
    UARTprintf("*****************************************************\n");
    UARTprintf("Analog Input: Internal Temperature Sensor\n");

    // ADC initialization
    ADCInit();

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
        ui32TempValueC = (1475 - ((2475 * ui32TempAvg)) / 4096)/10;

        // Display the temperature value on the console.
        //PrintTemps (ui32TempValueC);

        // (2-4) Display the temperature value on the console with timelog
        PrintTempsWithTime(ui32TempValueC);

        //
        // This function provides a means of generating a constant length
        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
        // 250ms arbitrarily.
        //
        SysCtlDelay(SysCtlClockGet() / clkscalevalue);
    }
}


//EOF


