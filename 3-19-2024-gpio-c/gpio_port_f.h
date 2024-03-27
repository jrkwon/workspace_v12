/*
 * gpio_port_f.h
 *
 *  Created on: Mar 19, 2024
 *      Author: jaerock
 */

#ifndef GPIO_PORT_F_H_
#define GPIO_PORT_F_H_


#define GPIO_PORTF_DATA_R   (*((unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R    (*((unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R  (*((unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R    (*((unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R    (*((unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R   (*((unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R     (*((unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R  (*((unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R   (*((unsigned long *)0x4002552C))

#define GPIO_LOCK_KEY       0x4C4F434B

#define SYSCTL_RCGCGPIO_R   (*((unsigned long *)0x400FE608))

/* funciton prototypes */
void init_gpio_port_f(void);

#endif /* GPIO_PORT_F_H_ */
