/*
 * app.h
 *
 *  Created on: May 27, 2022
 *      Author: pieraqua
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>

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

typedef struct{
    enEstadosAPP estado;
    enSubestadosAPP subEstado;
}STRUCT_APP;

STRUCT_APP stApp;

void vAPP_Init();
void vAPP_Poll();

static void svEstadoInicial();
static void svEstadoNVoltas();
static void svEstadoInicial();
static void svEstadoInicial();
static void svEstadoInicial();
static void svEstadoInicial();
static void svEstadoInicial();



#endif /* APP_H_ */
