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

LeituraTeclado1
    ;Coloca 1110
    MOV R1, #0x0D
    ;Output pro GPIO
    LDR R0, R2
    LDR R4, =#0xFFFFFFF0
    AND R0, R4
    ORR R0, R1
    STR R2, R0

    ;Le os gpio
    LDR R0, R2
    LDR R4, =#0x00000001
    AND R0, R4
    CMP R0, #0
    IT GT
    BGT FimLeituraTeclado

    MOV R6, #1
    ADD R5, #1

LoopLeituraTeclado1
    BSL R4, R4
    AND R0, R4
    ADD R6, #1
    CMP R6, #4
    IT EQ
    BEQ LeituraTeclado2
    CMP R0, #0
    ITEE GT
    BGT FimLeituraTeclado
    ADDEQ R5, #1
    BEQ LoopLeituraTeclado1

LeituraTeclado1
    ;Coloca 1110
    MOV R1, #0x0E
    ;Output pro GPIO
    LDR R0, R2
    LDR R4, =#0xFFFFFFF0
    AND R0, R4
    ORR R0, R1
    STR R2, R0

    ;Le os gpio
    LDR R0, R2
    LDR R4, =#0x00000001
    AND R0, R4
    CMP R0, #0
    IT GT
    BGT FimLeituraTeclado

    MOV R6, #1
    ADD R5, #1

LoopLeituraTeclado1
    BSL R4, R4
    AND R0, R4
    ADD R6, #1
    CMP R6, #4
    IT EQ
    BEQ LeituraTeclado2
    CMP R0, #0
    ITEE GT
    BGT FimLeituraTeclado
    ADDEQ R5, #1
    BEQ LoopLeituraTeclado1


LeituraTeclado2
    ;Coloca 1101
    MOV R1, #0x0D
    ;Output pro GPIO
    LDR R0, R2
    LDR R4, =#0xFFFFFFF0
    AND R0, R4
    ORR R0, R1
    STR R2, R0

    ;Le os gpio
    LDR R0, R2
    LDR R4, =#0x00000001
    AND R0, R4
    CMP R0, #0
    IT GT
    BGT FimLeituraTeclado

    MOV R6, #1
    ADD R5, #1

LoopLeituraTeclado2
    BSL R4, R4
    AND R0, R4
    ADD R6, #1
    CMP R6, #4
    IT EQ
    BEQ LeituraTeclado3
    CMP R0, #0
    ITEE GT
    BGT FimLeituraTeclado
    ADDEQ R5, #1
    BEQ LoopLeituraTeclado2


LeituraTeclado3
    ;Coloca 1011
    MOV R1, #0x0B
    ;Output pro GPIO
    LDR R0, R2
    LDR R4, =#0xFFFFFFF0
    AND R0, R4
    ORR R0, R1
    STR R2, R0

    ;Le os gpio
    LDR R0, R2
    LDR R4, =#0x00000001
    AND R0, R4
    CMP R0, #0
    IT GT
    BGT FimLeituraTeclado

    MOV R6, #1
    ADD R5, #1

LoopLeituraTeclado3
    BSL R4, R4
    AND R0, R4
    ADD R6, #1
    CMP R6, #4
    IT EQ
    BEQ LeituraTeclado4
    CMP R0, #0
    ITEE GT
    BGT FimLeituraTeclado
    ADDEQ R5, #1
    BEQ LoopLeituraTeclado3

LeituraTeclado4
    ;Coloca 0111
    MOV R1, #0x07
    ;Output pro GPIO
    LDR R0, R2
    LDR R4, =#0xFFFFFFF0
    AND R0, R4
    ORR R0, R1
    STR R2, R0

    ;Le os gpio
    LDR R0, R2
    LDR R4, =#0x00000001
    AND R0, R4
    CMP R0, #0
    IT GT
    BGT FimLeituraTeclado
    MOV R6, #1
LoopLeituraTeclado4
    BSL R4, R4
    AND R0, R4
    ;Loopa ate ler 4 bits
    ADD R6, #1
    CMP R6, #4
    ITT EQ
    MOVEQ R0, #0xFF
    BEQ FimLeituraTeclado
    ;Se o valor nao for zero, achamos.
    ;Caso contrario, continuamos.
    CMP R0, #0
    ITE GT
    BGT FimLeituraTeclado
    BEQ LoopLeituraTeclado4

FimLeituraTeclado
    MOV R0, R5
    POP {R1, R2, R3, R4, R5, PC}