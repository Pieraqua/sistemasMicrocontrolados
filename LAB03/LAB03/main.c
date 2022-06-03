

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

int main(void)
{
    vAPP_Init();
    vLEDS_Init();
    GPIO_Init();

    teste();

    /* Loop principal */
    while(1)
    {
        //vAPP_Poll();
        //vLEDS_Poll();

    }
    /* Nunca vai retornar */
	return 0;
}
