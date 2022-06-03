/*
 * display.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "display.h"

#define LCDControlBits GPIO_PORTM_DATA_BITS_R + 0x07
#define LCDDataBits GPIO_PORTK_DATA_BITS_R + 0xFF

typedef enum
{
    SIMB_A = 0x41,

}simbolosDisplay;

//delay um número de clocks
static void delay(uint16_t i)
{
    uint16_t z;
    for(z = 0; z < i; z++)
    {}
}

void displayChar(simbolosDisplay simbolo)
{
    LCDDataBits = simbolo;
}

uint8_t LCD_checkBusyFlag()
{
    uint32_t busyFlag;

    GPIO_PORTM_DIR_R = GPIO_PORTM_DIR_R & 0xFFF0;
    LCDControlBits = 0x06; // 00000 1(enable)1(read)0(rs)

    delay(5);
    busyFlag = LCDDataBits;
    delay(5);

    LCDControlBits = 0x06;
    GPIO_PORTM_DIR_R |= 0x000F;

    return (uint8_t)(busyFlag & 0x80 >> 7);
}

void LCD_clearDisplay()
{
    // Disable instructions
    LCDControlBits = 0x00;

    LCDDataBits = 0x01;

    // Instruction register, write, enable
    LCDControlBits =  0x01;


}

void lcdOn()
{
    // Disable instructions
    LCDControlBits = 0x00;

    // Instruction register, write, enable
    LCDControlBits =  0x07;
}

void lcdOff()
{
    LCDControlBits = ;
}
