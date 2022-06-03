/*
 * display.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "display.h"

typedef enum
{
    SIMB_A = 0x41,
    SIMB_B = 0x42,
    SIMB_C = 0x43,
    SIMB_D = 0x44,
    SIMB_E = 0x45,
    SIMB_F = 0x46,
    SIMB_G = 0x47,
    SIMB_H = 0x48,
    SIMB_I = 0x49,
    SIMB_J = 0x4A,
    SIMB_K = 0x4B,
    SIMB_L = 0x4C,
    SIMB_M = 0x4D,
    SIMB_N = 0x4E,
    SIMB_O = 0x4F,
    SIMB_P = 0x50,
    SIMB_Q = 0x51,
    SIMB_R = 0x52,
    SIMB_S = 0x53,
    SIMB_T = 0x54,
    SIMB_U = 0x55,
    SIMB_V = 0x56,
    SIMB_W = 0x57,
    SIMB_X = 0x58,
    SIMB_Y = 0x59,
    SIMB_Z = 0x5A,
    SIMB_INTERROGAÇÃO = 0x3F,
    SIMB_PONTO = 0x2E,

}simbolosDisplay;

void displayChar(simbolosDisplay simbolo)
{

    GPIO_DATA_K = simbolo;

}
