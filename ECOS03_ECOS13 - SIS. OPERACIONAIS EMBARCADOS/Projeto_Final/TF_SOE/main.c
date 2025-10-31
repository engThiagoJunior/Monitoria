/* ----------------------------------------------------------------------
 * DATE:        28. DEZEMBRO 2024
 * VERSION:    V1.0
 *
 * PROJETO:      PROJETO FINAL S.O. EMBARCADOS
 *
 * PROPOSTA INICIAL:
 * 
 * Desenvolvimento de um sistema de controle de ilumina��o inteligente 
 * utilizando a placa STM32F103 e o FreeRTOS. O sistema deve gerenciar 
 * m�ltiplos padr�es de ilumina��o em um painel. A luz de cada zona 
 * deve ser controlada com base em hor�rios programados, pressionamentos 
 * manuais de bot�es e acionamentos de sensores.
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 2024 FAZION, G.; J�NIOR, T. TODOS OS DIREITOS RESERVADOS.
 * 
 *----------------------------------------------------------------------------
 * 
 * N�MERO DE MATR�CULA:
 * GABRIEL FAZION DOS SANTOS - 2022014991
 * THIAGO DE OLIVEIRA SOUSA J�NIOR - 2023008774
 * 
 *---------------------------------------------------------------------------*/

#include "stm32f10x.h"
#include <cmsis_os.h>
#include "Board_LED.h"
#include <stdbool.h>

//DEFINICOES DE PERIFERICOS:
//LCD display
#define LCD_RS 15
#define LCD_EN 12
//Switches
#define SW1 12  //PB12
#define SW2 13  //PB13
#define SW3 14  //PB14
#define SW4 15  //PB15
#define SW5 5   //PB5
#define SW6 4   //PB4
#define SW7 3   //PB3
#define SW8 3   //PA3
#define SW9 4   //PA4
#define SW10 8  //PB8
#define SW11 9  //PB9
#define SW12 11 //PB11
#define SW13 10 //PB10
#define SW14 7  //PA7
#define SW15 15 //PC15
#define SW16 14 //PC14
#define SW17 13 //PC13
//LEDs
#define LED1 0  //PA0
#define LED2 1  //PA1
#define LED3 2  //PA2
#define LED4 15 //PA15
#define LED5 8  //PA8
#define LED6 6  //PA6
#define LED7 5  //PA5
#define LED8 11 //PA11
//Potentiometer
#define POT 1 //PB1
//Buzzer
#define BUZ 0 //PB0

//VARIAVEIS GLOBAIS:
//-VARIAVEIS DO ALGORITMO DE SUAVIZACAO
volatile float TIME_REAL = 300; 						//1s
volatile float TIME_PSEUDO = 300; 						//1s
volatile float FACTOR = 0.30;
//-VARIAVEL DEBOUNCE
#define DEBOUNCE_DELAY 45   							// Tempo de debounce
//-VARIAVEIS DE CONTROLE
volatile int NUM_LEDS_ATIVOS = 0;
char* FUNC=" 0";
char* BUTTON=" 0 ";
char* SW="0";
bool FLAG=false;

//FUNCOES:
//-FUNCOES LCD
void lcd_putValue(unsigned char value);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print(char * str);
void lcd_init();
void lcd_atualiza();
//-FUNCOES LED 
void led_par_impar() ; 														//FUNCAO 1 PDF
void led_gray(); 															//FUNCAO 2 PDF
void led_pot(); 															//FUNCAO 3 PDF
//-FUNCAO PERIFERICOS
void buzzer(); 																//FUNCAO 4 PDF 
void setBuzzerFrequency(uint16_t frequency);								//FUNCAO PARA USAR BUZZER
//-CONTROLE DE INTERRUPTOEES (SWITCHS)
void leitura_funcao();
void leitura_controle();
//-FUNCOES DIVERSAS
uint16_t readADC(); 														// LE O ADC RETORNA UM INTEIRO DE 16BITS
void smooth_Time();														
int button_debounce(GPIO_TypeDef *GPIOx, uint16_t pin);


//ID DAS THREADS:
//-LED
osThreadId T_led_par_impar_ID;
osThreadId T_led_gray_ID;
osThreadId T_led_pot_ID;
//-PERIFERICOS
osThreadId T_buzzer_ID;
osThreadId T_LCD_ID;
//-CONTROLE
osThreadId T_leitura_func_ID;
osThreadId T_leitura_cont_ID;
//-SUAVIZACAO
osThreadId T_smooth_Time_ID;

//DEFINICAO DE THREADS
//-LED
osThreadDef(led_par_impar, osPriorityNormal, 1, 0);
osThreadDef(led_gray, osPriorityNormal, 1, 0);
osThreadDef(led_pot, osPriorityNormal, 1, 0);
//-PERIFERICOS
osThreadDef(buzzer, osPriorityAboveNormal, 1, 0);
osThreadDef(lcd_atualiza, osPriorityRealtime, 1, 0);
//-CONTROLE
osThreadDef(leitura_funcao, osPriorityHigh, 1, 0);
osThreadDef(leitura_controle, osPriorityHigh, 1, 0);
//-SUAVIZACAO
osThreadDef(smooth_Time, osPriorityAboveNormal, 1, 0);

int main (void){
	//CONFIG OTAVIO:
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 					// Habilita o clock do AF (Fun��es Alternativas) para poder configurar as portas corretamente
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;  			// Desabilita o JTAG e configura o modo SWJ para evitar interfer�ncia com os pinos de I/O
	osDelay(100); 											// Atraso de 100ms para garantir a estabilidade ap�s as configura��es
	RCC->APB2ENR |= 0xFC |(1<<9);							// Habilita os clocks para os GPIOs e ADC1
	// Configura as sa�das para os LEDs
	ADC1->CR2 = 1;											// ADON = 1 (liga o ADC)
	ADC1->CR2 |= (1<<2); 									// Habilita a calibra��o do ADC
	osDelay(1);												//Espera 1us para garantir que o m�dulo ADC esteja estavel
	// Configura os pinos de entrada para os interruptores (bot�es)
	GPIOA->CRL = 0x43344333; 								// PA3, PA4 e PA7: entradas (interruptores)
	GPIOA->CRH = 0x33333333; 								// PA8 - PA15: sa�das (LEDs)
	// Configura os pinos de entrada para os interruptores (bot�es) adicionais
	GPIOB->CRL = 0x4444440B;								// PB0 configurado para sa�da+forma de onda alternada, pois est� conectado ao buzzer.
	GPIOB->CRH = 0x44444444; 								// Configura��o dos pinos superiores do GPIOB
	GPIOB->ODR = 0xF000; 									// Define o pull-up para PB12 at� PB15
	// Configura os pinos de sa�da para GPIOC
	GPIOC->CRH = 0x44444444; 								// Configura��o dos pinos superiores do GPIOC
	GPIOC->ODR = 0xFFFFFFFF; 								// Define o pull-up para todos os pinos de GPIOC
	// Desliga o LED 4 (PA4)
	GPIOA->ODR &= ~(1<<LED4); 								// Desliga o LED4 (PA4)
	
	lcd_init();												// Inicia configuracao LCD
	
	osKernelInitialize();                    				// initialize CMSIS-RTOS
	
	//CRIACAO DE THREADS
	//-LEDS
  	T_led_par_impar_ID = osThreadCreate(osThread(led_par_impar), NULL);
	T_led_gray_ID = osThreadCreate(osThread(led_gray), NULL);
	T_led_pot_ID = osThreadCreate(osThread(led_pot), NULL);
	//-PERFERICOS
	T_buzzer_ID = osThreadCreate(osThread(buzzer), NULL);
	T_LCD_ID = osThreadCreate(osThread(lcd_atualiza),NULL);
	//-CONTROLE
	T_leitura_func_ID = osThreadCreate(osThread(leitura_funcao), NULL);
	T_leitura_cont_ID = osThreadCreate(osThread(leitura_controle),NULL);
	//-SUAVIZACAO
	T_smooth_Time_ID = osThreadCreate(osThread(smooth_Time), NULL);
	
	osKernelStart();                        				// start thread execution 
	
	while(1){};
}

//FUNCOES LCD/OTAVIO
void lcd_putValue(unsigned char value){
	uint16_t aux;
	aux = 0x0000;
	GPIOA->BRR = (1<<5)|(1<<6)|(1<<8)|(1<<11);
	aux = value & 0xF0;
	aux = aux>>4;
	GPIOA->BSRR = ((aux&0x0008)<<8) | ((aux&0x0004)<<3) | ((aux&0x0002)<<5) | ((aux&0x0001)<<8);
	//GPIOA->BSRR = ;
	//GPIOA->BSRR = ;
	//GPIOA->BSRR = ;
	
	GPIOA->ODR |= (1<<LCD_EN); 
	osDelay(3);			
	GPIOA->ODR &= ~ (1<<LCD_EN);
	osDelay(1);	

	GPIOA->BRR = (1<<5)|(1<<6)|(1<<8)|(1<<11);
	//GPIOA->BSRR = value&0x0F; 
	aux = 0x0000;
	aux = value & 0x0F;
	GPIOA->BSRR = ((aux&0x0008)<<8) | ((aux&0x0004)<<3) | ((aux&0x0002)<<5) | ((aux&0x0001)<<8);
	//GPIOA->BSRR = (aux&0x0008)<<8;
	//GPIOA->BSRR = (aux&0x0004)<<6;
	//GPIOA->BSRR = (aux&0x0002)<<5;
	//GPIOA->BSRR = (aux&0x0001)<<5;
	//GPIOA->ODR = aux;
	
	GPIOA->ODR |= (1<<LCD_EN);
	osDelay(3);	
	GPIOA->ODR &= ~(1<<LCD_EN);	
	osDelay(1);			
	
	GPIOA->BRR |=(1<<LCD_RS)|(1<<LED5)|(1<<LED6)|(1<<LED7)|(1<<LED8);
}

void lcd_command(unsigned char cmd){
	GPIOA->ODR &= ~ (1<<LCD_RS);
	lcd_putValue(cmd);
}


void lcd_data(unsigned char data){
	GPIOA->ODR |= (1 << LCD_RS);    
  lcd_putValue(data); 
}

void lcd_print(char * str){
  unsigned char i = 0;

	while(str[i] != 0){
		lcd_data(str[i]);
		i++;
	}
}

//MUDANCA PARA ESCREVER AO INICIAR
void lcd_init(){
	osDelay(15);
	//GPIOA->ODR &= ~(1<<LCD_EN);
	osDelay(3);
	lcd_command(0x33); 
	osDelay(5);
	lcd_command(0x32); 
	osDelay(3000);
	lcd_command(0x28);
	osDelay(3);
	lcd_command(0x0e); 
	osDelay(3);
	lcd_command(0x01); 
	osDelay(3);
	lcd_command(0x06);
	osDelay(3);
	//
	lcd_command(0x01);
	lcd_command(0x80); 
	lcd_print("FUNCAO");
	lcd_print(FUNC);
	lcd_command(0xC0); 
	lcd_print("BOTAO");
	lcd_print(BUTTON);
	lcd_print("  SW");
	lcd_print(SW);
	osDelay(50);
}
//
void smooth_Time(){
	while(1){
		if (TIME_REAL != TIME_PSEUDO)
			TIME_REAL+=((TIME_PSEUDO-TIME_REAL)*FACTOR);
		osDelay(100);
	}
}
void led_par_impar() {
    //DEFINICAO DA SEQUENCIA EM UM VETOR
    unsigned int sequencia[8] = {
        (1 << LED1),                                						// LED1
        (1 << LED2),                                						// LED2
        (1 << LED1) | (1 << LED3),                  						// LED1 e LED3
        (1 << LED2) | (1 << LED4),                  						// LED2 e LED4
        (1 << LED1) | (1 << LED3) | (1 << LED5),    						// LED1, LED3 e LED5
        (1 << LED2) | (1 << LED4) | (1 << LED6),    						// LED2, LED4 e LED6
        (1 << LED1) | (1 << LED3) | (1 << LED5) | (1 << LED7), 				// LED1, LED3, LED5 e LED7
				(1 << LED2) | (1 << LED4) | (1 << LED6) | (1 << LED8) 		// LED2, LED4, LED6 e LED8 
    };
    int i;
		
		GPIOA->BRR = 0x00000000; //Apaga os LEDS
		
    while (1) {
		if(!FLAG){
			GPIOA->ODR = 0x00000000;
			osSignalWait(0x01, osWaitForever);
		}else{
			for (i = 0; i < 8; i++) {
				GPIOA->ODR |= sequencia[i]; //Liga os LEDs da sequencia atual
				osDelay(TIME_REAL);			//Delay
				GPIOA->ODR &= ~sequencia[i];//Liga os LEDs da sequencia atual
				if(!FLAG){
					GPIOA->ODR = 0x00000000;
					break;
				}
        	}
		}
    }
}

void led_gray() {
    int num_leds = 8; 								// LEDs de LED1 a LED8
    int max_estados = 1 << num_leds;  				// 2^8 estados possiveis

		unsigned int leds[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
	
    while (1){
		if(!FLAG){
			GPIOA->ODR = 0x00000000;
			osSignalWait(0x01, osWaitForever);
		}else{
			int i, j;
			
			for (i = 0; i < max_estados; i++){
				unsigned int estado_gray = i ^ (i >> 1); 		// Gera o estado em codigo gray

				GPIOA->ODR = 0x00000000; 						//Apaga os LEDS
		
				// Liga os LEDs conforme o estado atual do codigo gray
				for (j = 0; j < num_leds; j++)
					if (estado_gray & (1 << j)) 			// Verifica se o bit correspondente ja esta ligado
						GPIOA->ODR |= (1 << leds[j]);   // Liga o LED correspondente
				osDelay(TIME_REAL);								//Delay
				if(!FLAG){
					GPIOA->ODR = 0x00000000;
					break;
				}
			}
			GPIOA->ODR = 0x00000000; 									//Apaga os LEDS
		}
	}
}

void led_pot() {
    while (1) { 
		if(!FLAG){
			GPIOA->ODR = 0x00000000;
			osSignalWait(0x01, osWaitForever);
		}else{
			uint16_t ADC_VALUE = readADC();

			GPIOA->ODR = 0x00000000;

			// Atualiza os LEDs com base no valor do ADC
			switch (ADC_VALUE/8){ //(/8)Para funcionar com 0-512
				case 0 ... 56: // Nenhum LED ligado
					NUM_LEDS_ATIVOS = 0;
					break;
				case 57 ... 113: // Liga LED1
					GPIOA->ODR |= (1 << LED1);
					NUM_LEDS_ATIVOS = 1;
					break;
				case 114 ... 170: // Liga LED1 e LED2
					GPIOA->ODR |= (1 << LED1) | (1 << LED2);
					NUM_LEDS_ATIVOS = 2;
					break;
				case 171 ... 227: // Liga LED1, LED2 e LED3
					GPIOA->ODR |= (1 << LED1) | (1 << LED2) | (1 << LED3);
					NUM_LEDS_ATIVOS = 3;
					break;
				case 228 ... 284: // Liga LED1, LED2, LED3 e LED4
					GPIOA->ODR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
					NUM_LEDS_ATIVOS = 4;
					break;
				case 285 ... 341: // Liga at? LED5
					GPIOA->ODR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) | (1 << LED5);
					NUM_LEDS_ATIVOS = 5;
					break;
				case 342 ... 398: // Liga at? LED6
					GPIOA->ODR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) | (1 << LED5) | (1 << LED6);
					NUM_LEDS_ATIVOS = 6;
					break;
				case 399 ... 455: // Liga at? LED7
					GPIOA->ODR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) |
												(1 << LED5) | (1 << LED6) | (1 << LED7);
					NUM_LEDS_ATIVOS = 7;
					break;
				case 456 ... 512: // Liga todos os LEDs (incluindo LED8)
					GPIOA->ODR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4) |
								  (1 << LED5) | (1 << LED6) | (1 << LED7) | (1 << LED8);
					NUM_LEDS_ATIVOS = 8;
					break;
				default: // Caso inesperado
					GPIOA->ODR = 0x00000000; //Apaga os LEDS
					NUM_LEDS_ATIVOS = 0;
					break;
			}
			osDelay(100); // Pequeno atraso para estabilizar as leituras
		}
	}
}

void setBuzzerFrequency(uint16_t frequency){
    if (frequency == 0) {
        // Desliga o buzzer
        RCC->APB1ENR &= ~(1 << 1);  // Desabilita o timer 3
        return;
    }

    // Habilita o clock para o timer TIM3
    RCC->APB1ENR |= (1 << 1);   // Habilita o clock do timer 3
    uint32_t pclk1 = 42000000;  // Valor do clock do periferico, 42 MHz por padrao
    uint32_t prescaler = 1;     // Prescaler de 1 (sem divisao)

    uint32_t arr_value = pclk1 / (frequency * prescaler) - 1;

    // Ajuste o ARR e o CCR2 de acordo com a frequencia desejada
    TIM3->ARR = arr_value;        // Define o valor de ARR para gerar a frequ?ncia
    TIM3->CCR2 = arr_value / 2;   // Define o valor de CCR2 para o "duty cycle" de 50%

    // Configura o modo de PWM no canal 2
    TIM3->CCER = 0x1 << 8;       // CC2P = 0 (ativo em n?vel baixo), CC2E = 1 (habilita o canal)
    TIM3->CCMR2 = 0x0030;        // Modo PWM no canal 2 (toggle)

    // Inicia o timer
    TIM3->CR1 = 1;               // Habilita o timer

    osDelay(10); // Pequeno atraso para estabilizar
}

void buzzer() {
    while (1) { 
		if(!FLAG){
			GPIOA->ODR = 0x00000000;
			osSignalWait(0x01, osWaitForever);
		}else{
			// O NUM_LEDS_ATIVOS definidos na Theread que executa led_pot()
			switch (NUM_LEDS_ATIVOS) {
				case 0:
					setBuzzerFrequency(0); // Frequencia 0 = sem som
					break;
				case 1:
					setBuzzerFrequency(500); // 500 Hz
					break;
				case 2:
					setBuzzerFrequency(600); // 600 Hz
					break;
				case 3:
					setBuzzerFrequency(700); // 700 Hz
					break;
				case 4:
					setBuzzerFrequency(800); // 800 Hz
					break;
				case 5:
					setBuzzerFrequency(900); // 900 Hz
					break;
				case 6:
					setBuzzerFrequency(1000); // 1 kHz
					break;
				case 7:
					setBuzzerFrequency(1100); // 1.1 kHz
					break;
				case 8:
					setBuzzerFrequency(1200); // 1.2 kHz
					break;
				default:
					setBuzzerFrequency(0); // Frequencia 0 = sem som
					break;
			}
			osDelay(1000); // Pequeno atraso para estabilizar as leituras
			setBuzzerFrequency(0);
		}
	}
}

void leitura_funcao(){
	while(1){
		//FUNCAO 1
		if (button_debounce(GPIOB, (1 << SW5)))
		{
			FUNC=" 1";
			BUTTON=" C";
			SW="5";
			FLAG=!FLAG;
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			osSignalSet(T_led_par_impar_ID, 0x01);
		}else //FUNCAO 2
		if (button_debounce(GPIOB, (1 << SW6)))
		{
			FUNC=" 2";
			BUTTON=" D";
			SW="6";
			FLAG=!FLAG;
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			osSignalSet(T_led_gray_ID, 0x01);
		} else //FUNCAO 3
		if (button_debounce(GPIOB, (1 << SW7)))
		{
			FUNC=" 3";
			BUTTON=" E ";
			SW="7";
			FLAG=!FLAG;
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(110);
			osSignalSet(T_led_pot_ID, 0x01);
		} else //FUNCAO 4
		if (button_debounce(GPIOA, (1 << SW8)))
		{
			FUNC=" 4";
			BUTTON=" F";
			SW="8";
			FLAG=!FLAG;
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(150);
			osSignalSet(T_led_pot_ID, 0x01);
			osDelay(150);
			osSignalSet(T_buzzer_ID, 0x01);
		}
		osDelay(300);
	}
}

void leitura_controle() {
	while(1){
		//FUNCAO Y
		if(button_debounce(GPIOB, (1 << SW1)))
		{
			BUTTON=" Y";
			SW="1";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			TIME_PSEUDO = TIME_REAL / 2;
		} else
		//FUNCAO A
		if(button_debounce(GPIOB, (1 << SW2)))
		{
			BUTTON=" A";
			SW="2";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			TIME_PSEUDO = TIME_REAL * 2;
		} else
		//FUNCAO X
		if(button_debounce(GPIOB, (1 << SW3)))
		{
			BUTTON=" X";
			SW="3";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			TIME_PSEUDO = 1000;
		} else
		//FUNCAO B
		if(button_debounce(GPIOB, (1 << SW4)))
		{
			BUTTON=" B";
			SW="4";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			uint16_t valor = readADC()/8;
			osDelay(30);
			TIME_PSEUDO = valor;
		} else
		//FUNCAO L
		if(button_debounce(GPIOC, (1 << SW15)))
		{
			BUTTON=" L";
			SW="15";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			TIME_PSEUDO = 500;
		} else
		//FUNCAO M
		if(button_debounce(GPIOC, (1 << SW16)))
		{
			BUTTON=" M";
			SW="16";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			TIME_PSEUDO = 2000;
		} else
		//FUNCAO N
		if(button_debounce(GPIOC, (1 << SW17)))
		{
			BUTTON=" N";
			SW="17";
			osSignalSet(T_LCD_ID, 0x01);
			osDelay(50);
			TIME_PSEUDO = 10000;
		}
		osDelay(300);
	}
}


void lcd_atualiza(){		
	while(true){
		osSignalWait(0x01, osWaitForever);
		if(!FLAG){
			FUNC=" 0";
			BUTTON=" 0 ";
			SW="0";
		}
		lcd_command(0x01);
		lcd_command(0x80);
		lcd_print("FUNCAO");
		lcd_print(FUNC);
		lcd_command(0xC0);
		lcd_print("BOTAO");
		lcd_print(BUTTON);
		lcd_print("  SW");
		lcd_print(SW);
	}
}

uint16_t readADC(){
	uint16_t ADC_VALUE;
  ADC_VALUE = 0x0000;
	
	// Configura o ADC para ler o canal do potenci?metro
	ADC1->SQR3 = 9;   										// Escolhe o canal 9 como entrada 
	ADC1->CR2 = 1;    										// ADON = 1 (Inicicio da conversao)
	ADC1->CR2 |= 2;   										// Autocalibracao
	osDelay(2);      											// Pequeno atraso para estabilizar
	while ((ADC1->SR & (1 << 1)) == 0); 	// Aguarda o termino da conversao
	osDelay(50);
	// Le o valor convertido pelo ADC
	ADC_VALUE = ADC1->DR;
	
	// Retorna o valor convertido
	return ADC_VALUE;
}

int button_debounce(GPIO_TypeDef *GPIOx, uint16_t pin){
    if ((GPIOx->IDR & pin) == 0){
        osDelay(DEBOUNCE_DELAY);  				
		while((GPIOx->IDR & pin) == 0){}
        return 1;  										
    }else{
        return 0;  												
    }
}