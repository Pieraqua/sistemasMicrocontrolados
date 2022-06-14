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
    //Portas 0~2 e 4~7: Output
    GPIO_PORTM_DIR_R  |= 0xF7;
    //Digital enable
    GPIO_PORTM_AMSEL_R &= 0xFFF8;
    GPIO_PORTM_AFSEL_R &= 0xFFF8;
    GPIO_PORTM_DEN_R |= 0XF7;
    //Disable extra drive
    GPIO_PORTM_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTM_IM_R = 0x00;


    //Motor
    //Todos os gpio 0, 1, 2 e 3 H como Output Digital
    //Liga clock GPIO port H
    SYSCTL_RCGCGPIO_R |= 0x080;
    //Portas 0~3: Output
    GPIO_PORTH_AHB_DIR_R  |= 0x0F; //bitmap das portas
    //Digital enable
    GPIO_PORTH_AHB_AMSEL_R &= 0xFFF0;
    GPIO_PORTH_AHB_AFSEL_R &= 0xFFF0;
    GPIO_PORTH_AHB_DEN_R |= 0X0F;
    //Disable extra drive
    GPIO_PORTH_AHB_PC_R = 0x00;
    //Disable interrupts
    GPIO_PORTH_AHB_IM_R = 0x00;

    //teclado
    SYSCTL_RCGCGPIO_R |= 0x14;                 //Liga o clock para o PORTL e PORTM
    //while ((SYSCTL_RCGCGPIO&0x14)==0);       //Espera o clock
    GPIO_PORTL_CR_R  |= 0x0F;                  //Permite configurar os pinos do PORTL
    //GPIO_PORTM_CR_R  |= 0xF7;                //Permite configurar os pinos do PORTM
    //GPIO_PORTM_DIR_R |= 0x00;                //PM4 - PM7 são usados como linha e setados como digital input
    //GPIO_PORTM_PDR_R |= 0xF0;                //Liga resistor de pull down para o PORTM
    GPIO_PORTL_DEN_R |= 0xF0;                  //Seta PORTL como pinos digitais
    //GPIO_PORTM_DEN_R |= 0x1E;                //Seta PORTM como pinos digitais


}

