/*
 * motor.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */
#include "motor.h"

#define MotorControlBits (*(volatile uint32_t*)(GPIO_PORTH_AHB_DATA_BITS_R + 0x1 + 0x2 + 0x4 + 0x8))

void vMOTOR_Init()
{
    stMotor.estadoMotor = 0;
    stMotor.velocidade = 0xff; //parado
}

void vMOTOR_Poll()
{
    static uint32_t delay = 0;

    if(delay)
    {
        delay--;
    }
    switch(stMotor.estadoMotor)
        {
        case 0:
                //H1 = 1;
                //H0 = 0;
            if(!delay){
                MotorControlBits = 0x02;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor++;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 4;
            }
            break;

        case 1:
                //H2 = 1;
                //H1 = 0;
            if(!delay){
                MotorControlBits = 0x04;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor++;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 5;
            }
            break;

        case 2:
                //H3 = 1;
                //H2 = 0;
            if(!delay){
                MotorControlBits = 0x08;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor++;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 6;
            }
            break;

        case 3:
                //H0 = 1;
                //H3 = 0;
            if(!delay){
                MotorControlBits = 0x01;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor = 0;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 7;
            }
            break;
        case 4:
            //H1 = 1;
            //H2 = 1;
            if(!delay){
                MotorControlBits = 0x06;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor++;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 1;
            }
            break;

        case 5:
            //H2 = 1;
            //H3 = 1;
            if(!delay){
                MotorControlBits = 0x0D;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor++;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 2;
            }
            break;

        case 6:
            //H3 = 1;
            //H0 = 1;
            if(!delay){
                MotorControlBits = 0x09;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor++;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 3;
            }
            break;

        case 7:
            //H0 = 1;
            //H1 = 1;
            if(!delay){
                MotorControlBits = 0x03;
                delay = 500 * 800; //500ms
                if(stMotor.velocidade == 0)
                    stMotor.estadoMotor = 4;
                else if(stMotor.velocidade == 1)
                    stMotor.estadoMotor = 0;
            }
            break;
        }
}

