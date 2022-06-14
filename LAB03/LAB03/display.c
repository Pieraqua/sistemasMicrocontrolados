/*
 * display.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "display.h"

#define LCDControlBits (*(volatile uint32_t*)(0x40063000 + 0x4 + 0x8 + 0x10))
#define LCDDataBits (*((volatile uint32_t*)0x400613FC))


void display_MostraMensagem(const uint8_t* message, uint8_t size)
{
    uint8_t i;
    for(i = 0; i < size; i++)
    {
        displayChar((simbolosDisplay)*(message++));
    }
}


//delay um n�mero de clocks
void delay(uint32_t i)
{
    uint32_t z;
    for(z = 0; z < i; z++)
    {}
}

void LCD_Init()
{
    // Power-up delay
        delay(100 * 80000);                                 // initial 40 mSec delay

    // Reset the LCD controller
        /*LCD_writeCommand(lcd_FunctionReset);    // first part of reset sequence
        delay(10 * 80000);                                  // 4.1 mS delay (min)

        LCD_writeCommand(lcd_FunctionReset);    // second part of reset sequence
        delay(200 * 80);                                 // 100uS delay (min)

        LCD_writeCommand(lcd_FunctionReset);    // third part of reset sequence
        delay(200 * 80);                                 // this delay is omitted in the data sheet

    // Function Set instruction
        LCD_writeCommand(lcd_FunctionSet8bit);  // set mode, lines, and font
        delay(80 * 80);                                  // 40uS delay (min)

    // The next three instructions are specified in the data sheet as part of the initialization routine,
    //  so it is a good idea (but probably not necessary) to do them just as specified and then redo them
    //  later if the application requires a different configuration.

    // Display On/Off Control instruction
        LCD_writeCommand(lcd_DisplayOff);       // turn display OFF
        delay(80 * 40);                                  // 40 uS delay (min)

    // Clear Display instruction
        LCD_writeCommand(lcd_Clear);            // clear display RAM
        delay(4 * 80);                                   // 1.64 mS delay (min)

    // ; Entry Mode Set instruction
        LCD_writeCommand(lcd_EntryMode);        // set desired shift characteristics
        delay(80 * 40);                                  // 40 uS delay (min)

    // This is the end of the LCD controller initialization as specified in the data sheet, but the display
    //  has been left in the OFF condition.  This is a good time to turn the display back ON.

    // Display On/Off Control instruction
        LCD_writeCommand(lcd_DisplayOn);        // turn the display ON
        delay(80 * 40);
        */

        LCD_writeCommand(0x38);
        delay(80 * 40);
        LCD_writeCommand(0x06);
        delay(80 * 40);
        LCD_writeCommand(0x0E);
        delay(80 * 40);
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

void LCD_writeCommand(uint8_t command)
{
    LCDControlBits = 0x00;

    LCDDataBits = command;

    LCDControlBits = 0x04;
    delay(8000);

    LCDControlBits = 0x00;
    delay(8000);

}
