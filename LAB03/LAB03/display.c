/*
 * display.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "display.h"

typedef enum
{
    SIMB_A = 0x41,

}simbolosDisplay;

void displayChar(simbolosDisplay simbolo)
{

    GPIO_DATA_K = simbolo;

}
