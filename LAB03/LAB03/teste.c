/*
 * teste.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Paulo
 */

#include "teste.h"

void teste()
{
    lcdOn_Off();

    while(LCD_checkBusyFlag()){
        displayChar(SIMB_A);
    }

    while(LCD_checkBusyFlag()){
        displayChar(SIMB_B);
    }
    while(LCD_checkBusyFlag()){
        displayChar(SIMB_C);
    }
    while(LCD_checkBusyFlag()){
        displayChar(SIMB_D);
    }
    while(LCD_checkBusyFlag()){
        displayChar(SIMB_E);
    }
    while(LCD_checkBusyFlag()){
        displayChar(SIMB_F);
    }
    while(LCD_checkBusyFlag()){
        displayChar(SIMB_G);
    }

    delay(80000000);

    lcdOn_Off();
}


