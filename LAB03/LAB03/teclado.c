/*
 * teclado.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "teclado.h"

uint8_t teclado_OuveTecla()
{
    return 0;
}
/*declaração dos GPIO (n sei como declarar) */

/*Não entendi como declarar os endereços corretos, se puder, me ajuda aí*/

void vTECLADO_Init() {
      SYSCTL->RCGCGPIO |= 0x14;            //Liga o clock para o PORTL e PORTM
      while ((SYSCTL->RCGCGPIO&0x14)==0);  //Espera o clock
      GPIOL->CR  |= 0xF0;                  //Permite configurar os pinos do PORTL
      GPIOM->CR  |= 0x1E;                  //Permite configurar os pinos do PORTM
      GPIOM->DIR |= 0x00;                  //PM4 - PM7 são usados como linha e setados como digital input
      GPIOM->PDR |= 0x1E;                  //Liga resistor de pull down para o PORTM
      GPIOL->DEN |= 0xF0;                  //Seta PORTL como pinos digitais
      GPIOM->DEN |= 0x1E;                  //Seta PORTM como pinos digitais
}

/* teclaldo_getkey() retorna o valor da tecla pressionada percorrendo as colunas e linhas */
char teclado_getkey(void)
{
  while(1)
  {
    for(int i = 0; i < 4; i++)    //Da Scan nas colunas
    {
      GPIOL->DATA = (1U << i+4);
      delay_us(2);
      for(int j = 0; j < 4; j++)  //Da Scan nas linhas
      {
        if((GPIOM->DATA & 0x1E) & (1U << j+1))
          return symbol[j][i];
      }
    }
  }
}
