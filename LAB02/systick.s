    THUMB

    SYSTICK_VALUE   EQU 80000 ;Valor para systick de 1ms

    SYSTICK_CTL     EQU 0xE000E010
    SYSTICK_RELOAD  EQU 0xE000E014

    EXPORT SysTick_Handler
    IMPORT LedDelay

    AREA |.text|, CODE, READONLY, ALIGN=2

SysTickInit
    ;Ligar systick no NVIC
    

    ;Carrega 1ms no systick reload
    LDR R1, SYSTICK_RELOAD
    LDR R0, SYSTICK_VALUE
    STR R0, [R1]

    ;Liga o systick
    MOV R0, #0x7 ; 111 - Liga o clock do systick como sysclock, liga interrupcao, liga o systick
    LDR R1, SYSTICK_CTL
    STR R0, [R1]

    BX LR

SysTick_Handler
    MOV R0, #0
    MOV R2, =LedDelay
    LDR R1, [R2]
    CMP R0, R1
    ITT EQ
    SUBEQ R1, #1
    STR R1, [R2]

    BX LR
