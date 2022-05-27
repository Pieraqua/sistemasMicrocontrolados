/*
 * gpio.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */
#include <stdint.h>
#include <inc/tm4c1294ncpdt.h>

void GPIO_Init()
{
    SYSCTL_RCGCGPIO_R = 0x03;

    GPIO_PORTA_AHB_DIR_R = 0x0F;
}

