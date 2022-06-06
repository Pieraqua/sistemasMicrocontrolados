/*
 * teclado.h
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#ifndef TECLADO_H_
#define TECLADO_H_
#include <stdint.h>

uint8_t teclado_OuveTecla();

unsigned const byte LINHAS = 4;
unsigned const byte COLUNAS = 4;

#endif /* TECLADO_H_ */
unsigned char keys[LINHAS][COLUNAS] = {
                                   {'1','2','3','A'},
                                   {'4','5','6','B'},
                                   {'7','8','9','C'},
                                   {'*','0','#','D'}
                                 };


char teclado_getkey(void);
