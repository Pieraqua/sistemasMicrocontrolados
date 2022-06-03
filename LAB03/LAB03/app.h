/*
 * app.h
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>
#include "teclado.h"
#include "display.h"
#include "string.h"

typedef enum{
  ESTADO_INICIAL = 0,
  ESTADO_NVOLTAS,
  ESTADO_SENTIDO,
  ESTADO_VELOCIDADE,
  ESTADO_OPERANDO,
  ESTADO_FINAL
}enEstadosAPP;

typedef enum{
    Iniciando = 0,
    MostraMensagem,
    OuveTecla
}enSubestadosAPP;

typedef enum{
    MeioPasso = 0,
    PassoCompleto
}enVelocidades;

typedef enum{
    Direto = 0,
    Reverso
}enSentidosGiro;

typedef struct{
    enEstadosAPP estado;
    enSubestadosAPP subEstado;
    uint8_t nVoltas;
    enVelocidades velocidade;
    enSentidosGiro sentidoGiro;
}STRUCT_APP;

STRUCT_APP stApp;

void vAPP_Init();
void vAPP_Poll();

static void svEstadoInicial();
static void svEstadoNVoltas();
static void svEstadoOperando();
static void svEstadoSentido();
static void svEstadoFinal();
static void svEstadoVelocidade();



#endif /* APP_H_ */
