    THUMB
    ;Endereco GPIO para ligar o teclado
    GPIO_DATA_IN    EQU

    ;Endereco GPIO para ler do teclado
    GPIO_DATA_OUT   EQU

    AREA |.text|, CODE, READONLY, ALIGN=2

getTeclaPressionada
    PUSH {R0, R1, R2, R3, R4, R5, R6, R7, LR}

    LDR R2, =GPIO_DATA_IN
    LDR R3, =GPIO_DATA_OUT

    MOV R5, #0

LeituraTeclado
    ;Coloca 1110
    CMP R5, #0
    IT EQ
    MOVEQ R1, #0X0D
    ;Coloca 1101
    CMP R5, #4
    IT EQ
    MOVEQ R1, #0X0E
    ;Coloca 1011
    CMP R5, #8
    IT EQ
    MOVEQ R1, #0X0B
    ;Coloca 0111
    CMP R5, #12
    IT EQ
    MOVEQ R1, #0X07

    ;Joga para o gpio o valor
    LDR R0, R3
    AND R0, #0xF0
    ORR R0, R1
    STR R3, R0

    MOV R4, #1
LoopLeitura
    ;Se lemos 16 teclas, terminamos as leituras
    CMP R5, #16
    IT GE
    BGE FimLeituraTeclado
    ;LEMBRAR DE INVERTER R4
    LDR R7, =#0x10000
    CMP R4, R7
    IT EQ
    BEQ LeituraTeclado
    ;Le o teclado
    LDR R1, R2
    AND R0, R1, R4
    CMP R0, #0
    ITTTGT
    ADDGT R5, #1
    BSLGT R4, #1
    BGT LoopLeitura

FimLeituraTeclado
    ;Se retornar 16, nenhuma tecla foi lida.
    MOV R0, R5
    POP {R1, R2, R3, R4, R5, R6, R7, PC}