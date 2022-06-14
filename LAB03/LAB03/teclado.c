/*
 * teclado.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "teclado.h"

unsigned char keys[4][4] = {
                                   {'1','2','3','A'},
                                   {'4','5','6','B'},
                                   {'7','8','9','C'},
                                   {'*','0','#','D'}
                                 };
/*
uint8_t teclado_OuveTecla()
{
    return 0;
}

void vTECLADO_Init() {
      SYSCTL->RCGCGPIO |= 0x14;            //Liga o clock para o PORTL e PORTM
      while ((SYSCTL->RCGCGPIO&0x14)==0);  //Espera o clock
      GPIOL->CR  |= 0xF0;                  //Permite configurar os pinos do PORTL
      GPIOM->CR  |= 0x1E;                  //Permite configurar os pinos do PORTM
      GPIOM->DIR |= 0x00;                  //PM4 - PM7 são usados como linha e setados como digital input
      GPIOM->PDR |= 0x1E;                  //Liga resistor de pull down para o PORTM
      GPIOL->DEN |= 0xF0;                  //Seta PORTL como pinos digitais
      GPIOM->DEN |= 0x1E;                  //Seta PORTM como pinos digitais

      SYSCTL_RCGCGPIO_R |= 0x14;                   //Liga o clock para o PORTL e PORTM
      while ((SYSCTL_RCGCGPIO&0x14)==0);         //Espera o clock
      GPIO_PORTL_CR_R  |= 0xF0;                  //Permite configurar os pinos do PORTL
      GPIO_PORTM_CR_R  |= 0x1E;                  //Permite configurar os pinos do PORTM
      GPIO_PORTM_DIR_R |= 0x00;                  //PM4 - PM7 são usados como linha e setados como digital input
      GPIO_PORTM_PDR_R |= 0x1E;                  //Liga resistor de pull down para o PORTM
      GPIO_PORTL_DEN_R |= 0xF0;                  //Seta PORTL como pinos digitais
      GPIO_PORTM_DEN_R |= 0x1E;                  //Seta PORTM como pinos digitais
}
*/

/*teclado_getkey() retorna o valor da tecla pressionada percorrendo as colunas e linhas*/

char teclado_getkey(void)
{
  while(1)
  {
    for (int i = 0; i < 4; i++)    //Da Scan nas colunas
    {
      GPIO_PORTL_DATA_R = (1U << i+4);
      delay_us(2);
      for(int j = 0; j < 4; j++)   //Da Scan nas linhas
      {
        if((GPIO_PORTM_DATA_R & 0x1E) & (1U << j+1))
          return keys[j][i];
      }
    }
  }
}

