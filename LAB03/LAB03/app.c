/*
 * app.c
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#include "app.h"

void vAPP_Init()
{
    stApp.estado = ESTADO_INICIAL;
    stApp.subEstado = Iniciando;
}

void vAPP_Poll()
{
    switch(stApp.estado)
    {
    case ESTADO_INICIAL:
        svEstadoInicial();
        break;
    case ESTADO_NVOLTAS:
        svEstadoNVoltas();
        break;
    case ESTADO_SENTIDO:
        svEstadoSentido();
        break;
    case ESTADO_VELOCIDADE:
        svEstadoVelocidade();
        break;
    case ESTADO_OPERANDO:
        svEstadoOperando();
        break;
    case ESTADO_FINAL:
        svEstadoFinal();
        break;
    }

}
