/*
 * teste.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Paulo
 */

#include "teste.h"

void teste()
{


    do{
        displayChar(SIMB_A);
    }while(LCD_checkBusyFlag());

    do{
        displayChar(SIMB_B);
    }while(LCD_checkBusyFlag());
    do{
        displayChar(SIMB_C);
    }while(LCD_checkBusyFlag());
    do{
        displayChar(SIMB_D);
    }while(LCD_checkBusyFlag());
    do{
        displayChar(SIMB_E);
    }while(LCD_checkBusyFlag());
    do{
        displayChar(SIMB_F);
    }while(LCD_checkBusyFlag());
    do{
        displayChar(SIMB_G);
    }while(LCD_checkBusyFlag());

    delay(80000000);
}


