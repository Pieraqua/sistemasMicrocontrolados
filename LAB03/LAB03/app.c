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
        display_MostraMensagem("OLA.", strlen("OLA."));
        //displayChar(simbolo);
        /* Ao final, trocar o subestado de stApp */
        //if(terminou inicializacao)
        stApp.subEstado = OuveTecla;
        break;

    case OuveTecla:
        /* Trata ouvir tecla aqui */
        LCD_writeCommand(lcd_Clear);
        display_MostraMensagem("APERTE UM PARA INICIAR.", strlen("APERTE UM PARA INICIAR."));
        //displayChar(simbolosDisplay simbolo);

        uint8_t tecla = teclado_OuveTecla();

        if (tecla == 1){
            stApp.estado = ESTADO_NVOLTAS;
        }
        else{
        /* Ao final, trocar o estado de stApp */
        //if(terminou inicializacao)
        stApp.estado = ESTADO_INICIAL;
        }
        break;
    }

}
static void svEstadoNVoltas()
{
    uint8_t tecla;
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
            display_MostraMensagem("QUAL O NUMERO DE VOLTAS?", strlen("QUAL O NUMERO DE VOLTAS?"));
            //displayChar(simbolosDisplay simbolo);

            /* Ao final, trocar o subestado de stApp */
            //if(terminou inicializacao)
            stApp.subEstado = OuveTecla;
            break;

        case OuveTecla:
            /* Trata ouvir tecla aqui */
            tecla = teclado_OuveTecla(); // retorna caracter

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
            display_MostraMensagem("OPERANDO", strlen("OPERANDO"));
            //displayChar(simbolosDisplay simbolo);

            /* Ao final, trocar o subestado de stApp */
            //if(terminou inicializacao)
            stApp.subEstado = OuveTecla;
            break;

        case OuveTecla:
            /* Trata ouvir tecla aqui */
            /* N�o sei como fazer */
            if(1){
                stApp.estado = ESTADO_INICIAL;
            }
            else{
            /* Ao final, trocar o estado de stApp */
            //if(terminou inicializacao)
            stApp.estado = ESTADO_FINAL;
            }
            break;
        }

}
static void svEstadoSentido()
{
    uint8_t tecla;
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
            display_MostraMensagem("QUAL O SENTIDO DE GIRO?", strlen("QUAL O SENTIDO DE GIRO?"));
            //displayChar(simbolosDisplay simbolo);

            /* Ao final, trocar o subestado de stApp */
            //if(terminou inicializacao)
            stApp.subEstado = OuveTecla;
            break;

        case OuveTecla:
            /* Trata ouvir tecla aqui */
            tecla = teclado_OuveTecla();

            if(tecla == 1){
                stApp.sentidoGiro = Direto;
            }
            if(tecla == 2){
                stApp.sentidoGiro = Reverso;
            }


            /* Ao final, trocar o estado de stApp */
            //if(terminou inicializacao)
            stApp.estado = ESTADO_VELOCIDADE;
            break;
        }

}
static void svEstadoFinal()
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
                display_MostraMensagem("PROCESSO CONCLUIDO", strlen("PROCESSO CONCLUIDO"));
                //displayChar(simbolo);

                /* Ao final, trocar o subestado de stApp */
                //if(terminou inicializacao)
                stApp.subEstado = OuveTecla;
                break;

            case OuveTecla:
                /* Trata ouvir tecla aqui */
                display_MostraMensagem("APERTE UM PARA CONTINUAR", strlen("APERTE UM PARA CONTINUAR"));
                //displayChar(simbolo);

                uint8_t tecla = teclado_OuveTecla();

                if(tecla == 1){
                    stApp.estado = ESTADO_NVOLTAS;
                }
                else{
                /* Ao final, trocar o estado de stApp */
                //if(terminou inicializacao)
                //vai tudo pra solicita��o de voltas
                stApp.estado = ESTADO_FINAL;
                }
                break;
            }

}
static void svEstadoVelocidade()
{
    uint8_t tecla;
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
                display_MostraMensagem("QUAL A VELOCIDADE?", strlen("QUAL A VELOCIDADE?"));
                //displayChar(simbolo);


                /* Ao final, trocar o subestado de stApp */
                //if(terminou inicializacao)
                stApp.subEstado = OuveTecla;
                break;

            case OuveTecla:
                /* Trata ouvir tecla aqui */
                tecla = teclado_OuveTecla();

                if(tecla == 1){
                    stApp.velocidade = MeioPasso;
                }
                if(tecla == 2){
                    stApp.velocidade = PassoCompleto;
                }

                /* Ao final, trocar o estado de stApp */
                //if(terminou inicializacao)
                stApp.estado = ESTADO_OPERANDO;
                break;
            }

}
