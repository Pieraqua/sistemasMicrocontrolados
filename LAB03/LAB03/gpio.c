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
    //LCD Data bits
    //Todos os gpio K como Output Digital
    //Liga clock GPIO port K
    SYSCTL_RCGCGPIO_R |= 0x200;
    //Portas 0~7: Output
    GPIO_PORTK_DIR_R  |= 0xFF;
    //Digital enable
    GPIO_PORTK_AMSEL_R &= 0xFF00;
    GPIO_PORTK_AFSEL_R &= 0xFF00;
    GPIO_PORTK_DEN_R |= 0XFF;
    //Disable extra drive
    GPIO_PORTK_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTK_IM_R = 0x00;

    //LCD Control bits
    //PM0 = Instruction register (0) ou Data register (1)
    //PM1 = Read (1) / Write (0)
    //PM2 = Enable (inicia leitura)
    //Liga clock GPIO_M
    SYSCTL_RCGCGPIO_R |= 0x800;
    //Portas 0~2: Output
    GPIO_PORTM_DIR_R  |= 0x07;
    //Digital enable
    GPIO_PORTM_AMSEL_R &= 0xFFF8;
    GPIO_PORTM_AFSEL_R &= 0xFFF8;
    GPIO_PORTM_DEN_R |= 0X07;
    //Disable extra drive
    GPIO_PORTM_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTM_IM_R = 0x00;

    //Motor
    //Todos os gpio 0, 1, 2 e 3 H como Output Digital
    //Liga clock GPIO port H
    SYSCTL_RCGCGPIO_R |= 0x080;
    //Portas 0~3: Output
    GPIO_PORTH_AHB_DIR_R  |= 0x0F;
    //Digital enable
    GPIO_PORTH_AHB_AMSEL_R &= 0xFFF0;
    GPIO_PORTH_AHB_AFSEL_R &= 0xFFF0;
    GPIO_PORTH_AHB_DEN_R |= 0X0F;
    //Disable extra drive
    GPIO_PORTH_AHB_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTH_AHB_IM_R = 0x00;


}

