; Este programa deve esperar o usu�rio pressionar uma chave.
; Caso o usu�rio pressione uma chave, um LED deve piscar a cada 1 segundo.

; -------------------------------------------------------------------------------
        THUMB                        ; Instru��es do tipo Thumb-2
; -------------------------------------------------------------------------------
		
; Declara��es EQU - Defines
;<NOME>         EQU <VALOR>
; ========================
; Defini��es de Valores


; -------------------------------------------------------------------------------
; �rea de Dados - Declara��es de vari�veis
		AREA  DATA, ALIGN=2
		; Se alguma vari�vel for chamada em outro arquivo
		;EXPORT  <var> [DATA,SIZE=<tam>]   ; Permite chamar a vari�vel <var> a 
		                                   ; partir de outro arquivo
;<var>	SPACE <tam>                        ; Declara uma vari�vel de nome <var>
                                           ; de <tam> bytes a partir da primeira 
                                           ; posi��o da RAM		

		x DB 0
		y DB 0
		z DB 0
		t times 9 DB 0
		estadoDisplay DB 0
		ledTimer DW 0		

; -------------------------------------------------------------------------------
; �rea de C�digo - Tudo abaixo da diretiva a seguir ser� armazenado na mem�ria de 
;                  c�digo
        AREA    |.text|, CODE, READONLY, ALIGN=2

		; Se alguma fun��o do arquivo for chamada em outro arquivo	
        EXPORT Start                ; Permite chamar a fun��o Start a partir de 
			                        ; outro arquivo. No caso startup.s
									
		; Se chamar alguma fun��o externa	
        ;IMPORT <func>              ; Permite chamar dentro deste arquivo uma 
									; fun��o <func>
		IMPORT  PLL_Init
		IMPORT  SysTick_Init
		IMPORT  SysTick_Wait1ms			
		IMPORT  GPIO_Init
        IMPORT	Liga_Enable
		IMPORT  Desliga_Enable
		IMPORT  Liga_x			
		IMPORT  Liga_0
		IMPORT  Liga_1
		IMPORT  Liga_2
		IMPORT  Liga_3
		IMPORT  Liga_4
		IMPORT  Liga_5		
		IMPORT  Liga_6		
		IMPORT  Liga_7		
		IMPORT  Liga_8
		IMPORT  Liga_9
		IMPORT  Liga_E
		IMPORT  Liga_a	
		IMPORT  Liga_i

; -------------------------------------------------------------------------------
; Fun��o main()
Start  		
	BL PLL_Init                  ;Chama a subrotina para alterar o clock do microcontrolador para 80MHz
	BL SysTick_Init              ;Chama a subrotina para inicializar o SysTick
	BL GPIO_Init                 ;Chama a subrotina que inicializa os GPIO

;;Loop principal do codigo
MainLoop

	BL TabuadaPoll
	BL LEDPoll
	B MainLoop

;;Funcao de polling que trata de desligar o LED ao fim do timer
LEDPoll
	PUSH {R1, R0, LR}
	LDR R1, =ledTimer
	LDR R0, [R1]
	
	CMP R0, #0
	IT LE
	BLLE DesligaLED

	POP {R1, R0, LR}


;;Funcao de polling que trata de mostrar os valores corretos no display
TabuadaPoll
	PUSH {R1, R0, LR}
	;;Carrega R0 com o estado da maquina de estados
	STR R1, =estadoDisplay
	LDR R0, [R1]
	;;Se o estado for 0, mostra a mensagem de inicio. Caso contrario, mostra x*y=z
	CMP R0, #0
	ITE EQ
	BLEQ MostraMensagemInicio
	BLGE MostraTabuada

	POP {R0, PC}

IntTabuada
	PUSH {R2, R1, R0, LR}
	;;Altera estado display;;
	;;Troca o estado da maquina de estados do display
	MOV R0, #1
	LDR R1, =estadoDisplay
	STR R1, [R0]

	;;Verifica que foi interrompido pela tecla guardada em R0
	BL VerificaTecla

	;;Carrega o valor de t[x] em R2
	LDR R1, =t
	ADD R1, R0
	LDR R2, [R1]
	
	;;t[x]++
	ADD R2, #1

	;;t[x] == 9 ou 10?
	;;Caso 9 -> liga LED
	CMP R2, #9
	IT EQ
	BLEQ LigaLEDTimer
	
	;;Caso 10 -> t[x] = 0
	CMP R2, #10
	IT EQ
	MOVEQ R2, #0	

	;;Atualiza o valor de t[x]
	STR R1, [R2]

	;;x = x
	;; x = R0
	LDR R1, =x	
	STR R1, [R0]

	;;y = t[x]
	;;y = R2	
	LDR R1, =y	
	STR R1, [R2]

	;;z = x*t[x]
	;;z = R0*R2
	LDR R1, =z
	MUL R0, R2, R0
	STR R1, [R0]

	POP {R2, R1, R0, PC}

;;Funcao que interfaceia com o display para mostrar a mensagem de inicio
MostraMensagemInicio
	PUSH {LR}
	
	BL Liga_Enable      ;;Chama função para ligar Enable
	BL Liga_E	        ;;Chama função para ligar E	       
	BL Liga_a           ;;Chama função para ligar a
	BL Liga_i           ;;Chama função para ligar i
	BL Desliga_Enable   ;;Chama função para desligar Enable
	
	POP {PC}

;;Funcao que interfaceia com o display para mostrar x*y=z
MostraTabuada
	PUSH {LR}

	POP {PC}

;;Funcao que verifica o estado dos GPIOs para descobrir qual tecla foi pressionada no teclado. Guarda o resultado em R0.
VerificaTecla
	PUSH {LR}

	POP {PC}

;;Funcao que aumenta o valor do timer de LED para iniciar a contagem de 2 segundos do systick
LigaLEDTimer
	PUSH {R1, R0, LR}

	BL LigaLED

	LDR R1, =ledTimer
	;;COLOCAR 2 SEGUNDOS EM SYSTICK EM R0
	;; 0x07D0 = 2000 decimal
	MOV R0, #0xD0
	MOVT R0, #0x07
	STR R0, [R1]

	POP {R1, R0, PC}

;;Funcao que roda a cada tick do Systick
SystickLED
	LDR R1, =ledTimer
	LDR R0, R1
	CMP R0, #0
	ITT GE
	SUBGE R0, #1
	STRGE R0, [R1]

	BX LR

;;Liga o LED
LigaLED
	PUSH {LR}

	POP {PC}

;;Desliga o LED
DesligaLED
	PUSH {LR}

	POP {PC}

; -------------------------------------------------------------------------------------------------------------------------
; Fim do Arquivo
; -------------------------------------------------------------------------------------------------------------------------	
    ALIGN                        ;Garante que o fim da se��o est� alinhada 
    END                          ;Fim do arquivo
