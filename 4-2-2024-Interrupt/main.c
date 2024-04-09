#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"

// ---------------------------------------------------------------------------
// Interrupt handler prototypes
void IntPortFHandler(void);
// ---------------------------------------------------------------------------
// Function prototypes
void InitGPIO(void);
void EnablePortFInt(void);
void BlinkingLED(void);
void ToggleLED(void);

// ---------------------------------------------------------------------------
// Interrupt handler
void IntPortFHandler(void)
{
    // reset the flag
    uint32_t status = GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, status);

    // do something.
    ToggleLED();
}

// ---------------------------------------------------------------------------
void InitGPIO(void)
{
    // Set the clock to 80Mhz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlDelay(3);

    // for LEDs
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    // Enable the GPIO pin for the switches (SW1, SW2)
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

}

// ---------------------------------------------------------------------------
void EnablePortFInt(void)
{
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // button is negative logic.. 1 for not being pressed. 0 for being pressed
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);

    GPIOIntRegister(GPIO_PORTF_BASE, IntPortFHandler);
}

// ---------------------------------------------------------------------------
void BlinkingLED(void)
{
    uint32_t led_value = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);
    if (led_value == 0) {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
    }
    SysCtlDelay(5000000);
}

// ---------------------------------------------------------------------------
void ToggleLED(void) // red led
{
    uint32_t led_value = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);
    if (led_value == 0) {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
    }
}


// ---------------------------------------------------------------------------
/**
 * main.c
 */
int main(void)
{
    InitGPIO();
    EnablePortFInt();

    while(1) {
        SysCtlDelay(50);
    }

	return 0;
}
