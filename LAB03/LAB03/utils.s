; utils.s
; Desenvolvido para a placa EK-TM4C1294XL
; Código que apresenta algumas funcionalidades:
; - Altera a frequência do barramento usando o PLL
; - Configura o Systick para utilizar delays precisos

; -------------------------------------------------------------------------------------------------------------------------
; PLL
; -------------------------------------------------------------------------------------------------------------------------
; A frequência do barramento será 80MHz
; Representa o divisor para inicializar o PLL para a frequência desejada
; Frequência do barramento é 480MHz/(PSYSDIV+1) = 480MHz/(5+1) = 80 MHz



        .text
        .align 2
        .global  PLL_Init

;------------PLL_Init------------
; Configura o sistema para utilizar o clock do PLL
; Entrada: Nenhum
; Saída: Nenhum
; Modifica: R0, R1, R2, R3
PLL_Init
    ; Capítulo 5 do Datasheet
    ; 1) Depois que a configuração for pronta, o PIOSC provê o clock do sistema. Este,
    ;    passo garante que se a função já tenha sido chamada antes, o sistema desabilite
    ;    o clock do PLL antes de configurá-lo novamente.
    mov R1, #0xE0B0                 ; R1 = SYSCTL_RSCLKCFG_R (ponteiro)
    movt R1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (value)
    BIC R0, R0, #0x10000000        ; R0 = R0&~SYSCTL_RSCLKCFG_USEPLL (limpar o bit USEPLL bit para não clockar pelo PLL)
    STR R0, [R1]                               ; [R1] = R0
    ; 2) Ligar o MOSC limpando o bit NOXTAL bit no registrador SYSCTL_MOSCCTL_R.
    ; 3) Como o modo cristal é requerido, limpar o bit de PWRDN. O datasheet pede 
	;     para fazer estas duas operações em um único acesso de escrita ao SYSCTL_MOSCCTL_R.
    mov R1, #0xE07C                  ; R1 = SYSCTL_MOSCCTL_R (pointer)
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (value)
    BIC R0, R0, #0x00000004         ; R0 = R0&~SYSCTL_MOSCCTL_NOXTAL (limpa o bit NOXTAL para usar o cristal externo de 25 MHz)
    BIC R0, R0, #0x00000008          ; R0 = R0&~SYSCTL_MOSCCTL_PWRDN (limpa o bit PWRDN para ligar o oscilador principal)
    STR R0, [R1]                               ; [R1] = R0 (ambas alterações em um único acesso)
    ;    Esperar pelo bit MOSCPUPRIS ser setado no registrador SYSCTL_RIS_R register, indicando
	;    que o cristal modo MOSC está pronto
    mov R1, #0xE050                      ; R1 = SYSCTL_RIS_R (pointer)
	movt r1, #0x400F
PLL_Init_step3loop
    LDR R0, [R1]                               ; R0 = [R1] (value)
    ANDS R0, R0, #0x00000100        ; R0 = R0&SYSCTL_RIS_MOSCPUPRIS
    BEQ PLL_Init_step3loop                     ; if(R0 == 0), keep polling

    ; 4) Setar os campos OSCSRC e PLLSRC para 0x3 no registrador SYSCTL_RSCLKCFG_R
    ;    no offset 0x0B0.
    mov R1, #0xE0B0                ; R1 = SYSCTL_RSCLKCFG_R (pointer) 0x400FE0B0
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (value)
    BIC R0, R0, #0x00F00000      ; R0 = R0&~SYSCTL_RSCLKCFG_OSCSRC_M (limpar o campo system run/sleep clock source)
    ADD R0, R0, #0x00300000   ; R0 = R0 + SYSCTL_RSCLKCFG_OSCSRC_MOSC (configurar para temporariamente obter o clock do oscilador de 25MHz principal)
    BIC R0, R0, #0x0F000000      ; R0 = R0&~SYSCTL_RSCLKCFG_PLLSRC_M (limpar o campo PLL clock source)
    ADD R0, R0, #0x03000000   ; R0 = R0 + SYSCTL_RSCLKCFG_PLLSRC_MOSC (configurar para o clock do PLL do oscilador principal)
    STR R0, [R1]                               ; [R1] = R0
    ; 5) Se a aplicação também necessita que o MOSC seja a fonte de clock para deep-sleep
    ;    então programar o campo DSOSCSRC no registrador SYSCTL_DSCLKCFG_R para 0x3.
    mov R1, #0xE144                 ; R1 = SYSCTL_DSCLKCFG_R (pointer)
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (value)
    BIC R0, R0, #0x00F00000    ; R0 = R0&~SYSCTL_DSCLKCFG_DSOSCSRC_M (clear system deep-sleep clock source field)
    ADD R0, R0, #0x00300000 ; R0 = R0 + SYSCTL_DSCLKCFG_DSOSCSRC_MOSC (configure to get deep-sleep clock from main oscillator)
    STR R0, [R1]                               ; [R1] = R0
    ; 6) Escrever os registradores SYSCTL_PLLFREQ0_R e SYSCTL_PLLFREQ1_R com os valores de
    ;    Q, N, MINT, e MFRAC para configurar as configurações desejadas da frequência de VCO.
    ;    ************
    ;    fVC0 = (fXTAL/(Q + 1)/(N + 1))*(MINT + (MFRAC/1,024))
    ;    fVCO = 480,000,000 Hz (arbitrary, but presumably as small as needed)
	;    Para uma frequência que não seja um divisor inteiro de 480 MHz, mudar esta seção
;FXTAL  EQU 25000000                 ; fixa, o cristal está soldado no Launchpad
;Q      EQU        0
;N      EQU        4                 ; escolhido para ser a frequência de referência entre 4 e 30 MHz
;MINT   EQU       96                 ; 480,000,000 = (25,000,000/(0 + 1)/(4 + 1))*(96 + (0/1,024))
;MFRAC  EQU        0                 ; zero para reduzir o jitter
    ;    SysClk = fVCO / (PSYSDIV + 1)
;SYSCLK EQU (FXTAL/(Q+1)/(N+1))*(MINT+MFRAC/1024)/(PSYSDIV+1)
    mov R1, #0xE160                 ; R1 = SYSCTL_PLLFREQ0_R (ponteiro)
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (valor)
    mov R3, #0xFC00           ; R3 = SYSCTL_PLLFREQ0_MFRAC_M (máscar)
    movt r3, #0x000F
    BIC R0, R0, R3                             ; R0 = R0&~SYSCTL_PLLFREQ0_MFRAC_M (limpar o campo MFRAC)
    mov r3, #0  ; R3 = (MFRAC<<SYSCTL_PLLFREQ0_MFRAC_S) (valor deslocado)
    ADD R0, R0, R3                             ; R0 = R0 + (MFRAC<<SYSCTL_PLLFREQ0_MFRAC_S) (configurar MFRAC como definido acima)
	mov R3, #0x03FF            ; R3 = SYSCTL_PLLFREQ0_MINT_M (máscara)
    BIC R0, R0, R3                             ; R0 = R0&~SYSCTL_PLLFREQ0_MINT_M (limpar o campo MINT)
    ADD R0, R0, #96; R0 = R0 + (MINT<<SYSCTL_PLLFREQ0_MINT_S) (configurar MINT como definido acima)
    STR R0, [R1]                               ; [R1] = R0 (MFRAC e MINT alteraram mas não estão fixados ainda)
    mov R1, #0xE164
    movt r1, #0x400F                 ; R1 = SYSCTL_PLLFREQ1_R (ponteiro)
    LDR R0, [R1]                               ; R0 = [R1] (value)
    BIC R0, R0, #0x00001F00           ; R0 = R0&~SYSCTL_PLLFREQ1_Q_M (limpar o campo Q)
    ADD R0, R0, #0      ; R0 = R0 + (Q<<SYSCTL_PLLFREQ1_Q_S) (configurar Q como definido acima)
    BIC R0, R0, #0x0000001F           ; R0 = R0&~SYSCTL_PLLFREQ1_N_M (limpar o campo N)
    ADD R0, R0, #4     ; R0 = R0 + (N<<SYSCTL_PLLFREQ1_N_S) (configurar N como definido acima)
    STR R0, [R1]                               ; [R1] = R0 (Q e N alteraram mas não estão fixados ainda)
    mov r1, #0xE160
    movt R1, #0x400F  ; R1 = SYSCTL_PLLFREQ0_R (ponteiro)
    LDR R0, [R1]                               ; R0 = [R1] (valor)
    ORR R0, R0, #0x00800000        ; R0 = R0|SYSCTL_PLLFREQ0_PLLPWR (ligar a energia para o PLL)
    STR R0, [R1]                               ; [R1] = R0
    mov R1, #0xE0B0                ; R1 = SYSCTL_RSCLKCFG_R (ponteiro)
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (valor)
    ORR R0, R0, #0x40000000       ; R0 = R0|SYSCTL_RSCLKCFG_NEWFREQ (fixar as mudanças no registrador)
    STR R0, [R1]                               ; [R1] = R0
    ; 7) Escrever o registrador SYSCTL_MEMTIM0_R para a nova configuração de clock.
    ;    ************
    ;    Configurar os parâmetros de tempo para as memórias Flash e EEPROM que 
	;    dependem da frequência do clock do sistema. Ver a Tabela 5-12 do datasheet.
    mov R1, #0xE0C0                  ; R1 = SYSCTL_MEMTIM0_R (ponteiro)
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (valor)
    mov R3, #0x03EF                        ; R3 = 0x03EF03EF (máscara)
    movt r3, #0x03EF
    BIC R0, R0, R3                             ; R0 = R0&~0x03EF03EF (limpar os campos EBCHT, EBCE, EWS, FBCHT, FBCE, e FWS fields)
    mov R2, #0xB400                            ; R2 = (FXTAL/(Q+1)/(N+1))*(MINT+MFRAC/1024)/(PSYSDIV+1)
    movt r2, #0x04C4
    mov R3, #0x0E00                          ; R3 = 80,000,000 (value)
    movt r3, #0x0727
    CMP R2, R3                                 ; é R2 (SysClk) <= R3 (120,000,000 Hz)?
    BLS PLL_Init_step7fullspeed                ; se sim, pular o próximo teste
PLL_Init_step7toofast                          ; 120 MHz < SysClk: "too fast"
    ; Um configuração é inválida e o PLL não pode operar mais rápido que 120MHz.
    ; Pula o resto da inicialização, levando o sistema a operar pelo MOSC
    ; que é o cristal de 25MHz.
    BX  LR                                     ; retorna
PLL_Init_step7fullspeed                        ; 100 MHz < SysClk <= 120 MHz: "full speed"
    mov R3, #0xE100                         ; R3 = 100,000,000 (valor)
    movt r3, #0x5F5
    CMP R2, R3                                 ; é R2 (SysClk) <= R3 (100,000,000 Hz)?
    BLS PLL_Init_step7veryfast                 ; se sim, pula o próximo teste
    mov R3, #0x0185                        ; R3 = 0x01850185 (valores deslocados)
    movt r3, #0x0185
    ADD R0, R0, R3                             ; R0 = R0 + 0x01850185 (FBCHT/EBCHT = 6, FBCE/EBCE = 0, FWS/EWS = 5)
    B   PLL_Init_step7done                     ; branch incondicional para o fim
PLL_Init_step7veryfast                         ; 80 MHz < SysClk <= 100 MHz: "very fast"
    mov R3, #0xB400                          ; R3 = 80,000,000 (valor)
    movt r3, #0x04C4
    CMP R2, R3                                 ; é R2 (SysClk) <= R3 (80,000,000 Hz)?
    BLS PLL_Init_step7fast                     ; se sim, pula o próximo teste
    mov R3, #0x0144                        ; R3 = 0x01440144 (valores deslocados)
    movt r3, #0x0144
    ADD R0, R0, R3                             ; R0 = R0 + 0x01440144 (FBCHT/EBCHT = 5, FBCE/EBCE = 0, FWS/EWS = 4)
    B   PLL_Init_step7done                     ; branch incondicional para o fim
PLL_Init_step7fast                             ; 60 MHz < SysClk <= 80 MHz: "fast"
    mov R3, #0x8700                          ; R3 = 60,000,000 (valor)
    movt r3, #0x0393
    CMP R2, R3                                 ; é R2 (SysClk) <= R3 (60,000,000 Hz)?
    BLS PLL_Init_step7medium                   ; se sim, pula o próximo teste
    mov R3, #0x0103                        ; R3 = 0x01030103 (valores deslocados)
    movt r3, #0x0103
    ADD R0, R0, R3                             ; R0 = R0 + 0x01030103 (FBCHT/EBCHT = 4, FBCE/EBCE = 0, FWS/EWS = 3)
    B   PLL_Init_step7done                     ; branch incondicional para o fim
PLL_Init_step7medium                           ; 40 MHz < SysClk <= 60 MHz: "medium"
    mov R3, #0x5A00                          ; R3 = 40,000,000 (valor)
    movt r3, #0x0262
    CMP R2, R3                                 ; é R2 (SysClk) <= R3 (40,000,000 Hz)?
    BLS PLL_Init_step7slow                     ; se sim, pula o próximo teste
    ADD R0, R0, #0x00C200C2                    ; R0 = R0 + 0x00C200C2 (FBCHT/EBCHT = 3, FBCE/EBCE = 0, FWS/EWS = 2)
    B   PLL_Init_step7done                     ; branch incondicional para o fim
PLL_Init_step7slow                             ; 16 MHz < SysClk <= 40 MHz: "slow"
    mov R3, #0x2400                          ; R3 = 16,000,000 (value)
    movt r3, #0x00F4
    CMP R2, R3                                 ; é R2 (SysClk) <= R3 (16,000,000 Hz)?
    BLS PLL_Init_step7veryslow                 ; se sim, pula o próximo teste
    ADD R0, R0, #0x00810081                    ; R0 = R0 + 0x00810081 (FBCHT/EBCHT = 2, FBCE/EBCE = 1, FWS/EWS = 1)
    B   PLL_Init_step7done                     ; branch incondicional para o fim
PLL_Init_step7veryslow                         ; SysClk == 16 MHz: "very slow"
    mov R3, #0x2400                          ; R3 = 16,000,000 (value)
    movt r3, #0x00F4
    CMP R2, R3                                 ; é R2 (SysClk) < R3 (16,000,000 Hz)?
    BLO PLL_Init_step7extremelyslow            ; se sim, pula o próximo teste
    ADD R0, R0, #0x00200020                    ; R0 = R0 + 0x00200020 (FBCHT/EBCHT = 0, FBCE/EBCE = 1, FWS/EWS = 0)
    B   PLL_Init_step7done                     ; branch incondicional para o fim
PLL_Init_step7extremelyslow                    ; SysClk < 16 MHz: "extremely slow"
    ADD R0, R0, #0x00000000                    ; R0 = R0 + 0x00000000 (FBCHT/EBCHT = 0, FBCE/EBCE = 0, FWS/EWS = 0)
PLL_Init_step7done
    STR R0, [R1]                               ; [R1] = R0 (SYSCTL_MEMTIM0_R alterado mas não fixado ainda)
    ; 8) Espera pelo registrador SYSCTL_PLLSTAT_R indicar que o PLL atingiu travamento
    ;    no novo ponto de operação (ou que um período de timeout passou e o travamento
    ;    falhou, que no caso uma condição de erro existe e esta sequência é abandonada
    mov R1, #0xE168                  ; R1 = SYSCTL_PLLSTAT_R (pointer)
    movt r1, #0x400F
    MOV R2, #0                                 ; R2 = 0 (timeout counter)
    MOV R3, #0xFFFF                            ; R3 = 0xFFFF (value)
PLL_Init_step8loop
    LDR R0, [R1]                               ; R0 = [R1] (value)
    ANDS R0, R0, #0x00000001          ; R0 = R0&SYSCTL_PLLSTAT_LOCK
    BNE PLL_Init_step8done                     ; se (R0 != 0), terminar polling
    ADD R2, R2, #1                             ; R2 = R2 + 1 (incrementar o contador de timeout)
    CMP R2, R3                                 ; se (R2 < 0xFFFF), continuar o polling
    BLO PLL_Init_step8loop
    ; O PLL nunca travou ou não está ligado.
	; Pular o resto da inicialização, levando o sistema ser clockado pelo MOSC,
	; que é um cristal de 25MHz.
    BX  LR                                     ; return
PLL_Init_step8done
    ; 9)Escrever o valor do PSYSDIV no registrador SYSCTL_RSCLKCFG_R, setar o bit USEPLL para
    ;   ser habilitado e setar o bit MEMTIMU.
    mov R1, #0xE0B0                 ; R1 = SYSCTL_RSCLKCFG_R (ponteiro)
    movt r1, #0x400F
    LDR R0, [R1]                               ; R0 = [R1] (valor)
    mov R3, #0x03FF         ; R3 = SYSCTL_RSCLKCFG_PSYSDIV_M (mascara)
    BIC R0, R0, R3                             ; R0 = R0&~SYSCTL_RSCLKCFG_PSYSDIV_M (limpar o campo PSYSDIV)
    ADD R0, R0, #5; R0 = R0 + (PSYSDIV&SYSCTL_RSCLKCFG_PSYSDIV_M) (configurar PSYSDIV como definido acima)
    ORR R0, R0, #0x80000000       ; R0 = R0|SYSCTL_RSCLKCFG_MEMTIMU (setar o bit MEMTIMU para atualizar os parâmetros de temporização de memória)
    ORR R0, R0, #0x10000000        ; R0 = R0|SYSCTL_RSCLKCFG_USEPLL (setar o bit USEPLL para pegar o clock do PLL)
    STR R0, [R1]                               ; [R1] = R0 (execução e acesso são suspensas enquanto as atualizações na temporização da memória são atualizadas)
    BX  LR                                     ; return


; -------------------------------------------------------------------------------------------------------------------------
; Fim do Arquivo
; -------------------------------------------------------------------------------------------------------------------------
    .ALIGN                        ;Garante que o fim da seção está alinhada
    .END                          ;Fim do arquivo
