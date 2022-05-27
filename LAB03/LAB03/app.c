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
    stApp.nVoltas = 0;
    stApp.velocidade = MeioPasso;
    stApp.sentidoGiro = Direto;
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

static void svEstadoInicial()
{
    switch(stApp.subEstado)
    {
    case Iniciando:
        /* Inicializa aqui */

        /* Ao final, trocar o subestado de stApp */
        //if(terminou inicializacao)
        stApp.subEstado = MostraMensagem;
        break;

    case MostraMensagem:
        /* Mostra a mensagem aqui */


        /* Ao final, trocar o subestado de stApp */
        //if(terminou inicializacao)
        stApp.subEstado = OuveTecla;
        break;

    case OuveTecla:
        /* Trata ouvir tecla aqui */

        /* Ao final, trocar o estado de stApp */
        //if(terminou inicializacao)
        stApp.estado = ESTADO_NVOLTAS;
        break;
    }

}
static void svEstadoNVoltas()
{
    switch(stApp.subEstado)
        {
        case Iniciando:
            /* Inicializa aqui */

            /* Ao final, trocar o subestado de stApp */
            //if(terminou inicializacao)
            stApp.subEstado = MostraMensagem;
            break;

        case MostraMensagem:
            /* Mostra a mensagem aqui */
            display_MostraMensagem("mensagem");

            /* Ao final, trocar o subestado de stApp */
            //if(terminou inicializacao)
            stApp.subEstado = OuveTecla;
            break;

        case OuveTecla:
            /* Trata ouvir tecla aqui */
            uint8_t tecla = teclado_OuveTecla(); // retorna caracter

            if(tecla >= '0' && tecla <= '9')
            {
                if(tecla == '0')
                    stApp.nVoltas = 10;
                else
                    stApp.nVoltas = tecla - '0';

                /* Ao final, trocar o estado de stApp */
                stApp.estado = ESTADO_SENTIDO;
            }


            break;
        }
}
static void svEstadoOperando()
{

}
static void svEstadoSentido()
{

}
static void svEstadoFinal()
{

}
static void svEstadoVelocidade()
{

}
