/*
 * led.h
 *
 *  Created on: Apr 9, 2024
 *      Author: jaerock
 */

#ifndef LED_H_
#define LED_H_

#define LED_GREEN  GPIO_PIN_3
#define LED_BLUE   GPIO_PIN_2
#define LED_RED    GPIO_PIN_1

// function prototypes
void InitPortF(void);

void ToggleLED(uint32_t led_type);

//void ToggleGreenLED(void);
//void ToggleBlueLED(void);
//void ToggleRedLED(void);


#endif /* LED_H_ */
