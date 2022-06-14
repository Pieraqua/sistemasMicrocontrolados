/*
 * teclado.h
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */
#ifndef TECLADO_H_
#define TECLADO_H_
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"

uint8_t teclado_OuveTecla();




char teclado_getkey(void);
#endif /* TECLADO_H_ */

