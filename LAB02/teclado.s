    THUMB
    ;Endereco GPIO para ligar o teclado
    GPIO_DATA_IN    EQU

    ;Endereco GPIO para ler do teclado
    GPIO_DATA_OUT   EQU

    AREA |.text|, CODE, READONLY, ALIGN=2

getTeclaPressionada
    PUSH {R0, R1, R2, R3, R4, R5}

    LDR R2, GPIO_DATA_IN
    LDR R3, GPIO_DATA_OUT

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

FimLeituraTeclado
    MOV R0, R5
    POP {R1, R2, R3, R4, R5, PC}