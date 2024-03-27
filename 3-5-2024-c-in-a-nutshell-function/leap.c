/*
 * leap.c
 *
 *  Created on: Mar 5, 2024
 *      Author: jrkwon
 */
#include "leap.h"

int leap_year(int year)
{
    int leap = 0; // 0: false, 1: true

    if ((year%4 == 0) && (year%100 != 0))
        leap = 1;
    if (year%400 == 0)
        leap = 1;

    return leap;
}


