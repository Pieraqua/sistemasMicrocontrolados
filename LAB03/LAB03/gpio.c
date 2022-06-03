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
    //Todos os gpio K como Output Digital
    //Liga clock GPIO port K
    SYSCTL_RCGCGPIO_R |= 0x20;
    //Portas 0~7: Output
    GPIO_PORTK_DIR_R  |= 0x0F;
    //Digital enable
    GPIO_PORTK_AMSEL_R &= 0xFFF0;
    GPIO_PORTK_AFSEL_R &= 0xFFF0;
    GPIO_PORTK_DEN_R |= 0X0F;
    //Disable extra drive
    GPIO_PORTK_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTK_IM_R = 0x00;

    //PM0 = Instruction register (0) ou Data register (1)
    //PM1 = Read (1) / Write (0)
    //PM2 = Enable (inicia leitura)
    //Liga clock GPIO_M
    SYSCTL_RCGCGPIO_R |= 0x80;
    //Portas 0~2: Output
    GPIO_PORTK_DIR_R  |= 0x07;
    //Digital enable
    GPIO_PORTK_AMSEL_R &= 0xFFFA;
    GPIO_PORTK_AFSEL_R &= 0xFFF0;
    GPIO_PORTK_DEN_R |= 0X0F;
    //Disable extra drive
    GPIO_PORTK_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTK_IM_R = 0x00;


}

