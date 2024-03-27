/*
 * sw.c
 *
 *  Created on: Mar 19, 2024
 *      Author: jaerock
 */


#define PF4                 (*((unsigned long *)0x40025040)) /* SW1 - left */
#define PF0                 (*((unsigned long *)0x40025004)) /* SW2 - right */

#define SW1                 0x10
#define SW2                 0x01

/*
     4 3210
  ---S LLLS
  not being pressed: 0---*

  return 1 if the left switch is pressed
  return 0 otherwise
*/
char is_left_switch_pressed(void)
{
    int sw_value = PF4;

    /* button not pressed */
    if(sw_value == SW1)
       return 0;
    return 1;
}


