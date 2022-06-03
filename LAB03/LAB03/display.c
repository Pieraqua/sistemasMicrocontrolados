/*
 * display.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "display.h"

#define LCDControlBits (*(volatile uint32_t*)(0x40063000 + 0x4 + 0x8 + 0x10))
#define LCDDataBits (*((volatile uint32_t*)0x400613FC))



void display_MostraMensagem()
{}


//delay um número de clocks
void delay(uint32_t i)
{
    uint32_t z;
    for(z = 0; z < i; z++)
    {}
}

void displayChar(simbolosDisplay simbolo)
{
    // Disable instructions
    LCDControlBits = 0x00;

    LCDDataBits = simbolo;

    // Instruction register, write, enable
    LCDControlBits =  0x05;
    delay(WAIT_DELAY);
    LCDControlBits = 0x00;
}

uint8_t LCD_checkBusyFlag()
{
    uint32_t busyFlag;

    GPIO_PORTM_DIR_R = GPIO_PORTM_DIR_R & 0xFFF8;
    LCDControlBits = 0x06; // 00000 1(enable)1(read)0(rs)

    delay(WAIT_DELAY);
    busyFlag = LCDDataBits;
    delay(WAIT_DELAY);

    LCDControlBits = 0x00;
    GPIO_PORTM_DIR_R |= 0x0007;

    return (uint8_t)((busyFlag & 0x80) >> 7);
}

void LCD_clearDisplay()
{
    // Disable instructions
    LCDControlBits = 0x00;

    LCDDataBits = 0x01;

    // Instruction register, write, enable
    LCDControlBits =  0x01;
    delay(WAIT_DELAY);
    LCDControlBits = 0x00;
}

void lcdOn_Off()
{
    // Disable instructions
    LCDControlBits = 0x00;

    //Liga display e cursor mas não blinking
    LCDDataBits = 0x0E;

    // Instruction register, write, enable
    LCDControlBits =  0x01;
    delay(WAIT_DELAY);
    LCDControlBits = 0x00;
}

void LCD_Init()
{
    // Disable instructions
    LCDControlBits = 0x00;

    //Liga display e cursor mas não blinking
    LCDDataBits = 0x30;

    // Instruction register, write, enable
    LCDControlBits =  0x01;
    delay(WAIT_DELAY);
    // Disable instructions
    LCDControlBits = 0x00;

    //Liga display e cursor mas não blinking
    LCDDataBits = 0x06;

    // Instruction register, write, enable
    LCDControlBits =  0x01;
    delay(WAIT_DELAY);
    LCDControlBits = 0x00;
}

