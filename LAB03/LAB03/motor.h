/*
 * motor.h
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"

typedef struct
{
    uint8_t estadoMotor;
    uint8_t velocidade;
}STRUCT_MOTOR;

STRUCT_MOTOR stMotor;

void vMOTOR_Init();

void vMOTOR_Poll();

#endif /* MOTOR_H_ */
