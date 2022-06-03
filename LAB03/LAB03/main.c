

/**
 * main.c
 */

#include <stdint.h>
#include <inc/hw_memmap.h>
#include <inc/tm4c1294ncpdt.h>

#include "app.h"
#include "leds.h"
#include "teste.h"
#include "gpio.h"
#include "display.h"
#include "motor.h"

extern PLL_Init();

//delay um n�mero de clocks
/*void delay(uint32_t i)
{
    uint32_t z;
    for(z = 0; z < i; z++)
    {}
}*/

void main(void)
{

    PLL_Init();
    vAPP_Init();
    vLEDS_Init();
    GPIO_Init();

    delay(80000 * 50); //50ms

    LCD_Init();
    vMOTOR_Init();

    stMotor.velocidade = 0;

    /* Loop principal */
    while(1)
    {
        vMOTOR_Poll();
        //vAPP_Poll();
        //vLEDS_Poll();

    }
}
