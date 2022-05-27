

/**
 * main.c
 */

#include <stdint.h>
#include <inc/hw_memmap.h>
#include <inc/tm4c1294ncpdt.h>

int main(void)
{
    GPIO_PORTC_AHB_DATA_R = 0xFFFF;
	return 0;
}
