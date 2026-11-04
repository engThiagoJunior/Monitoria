#include "stm32f10x.h"
#include <cmsis_os.h>
#include "Board_LED.h"
#include "GPIO_STM32F10x.h"

/*----------------------------------------------------------------------------
  Definição dos pinos
 *---------------------------------------------------------------------------*/
// LEDs
#define LED1 0  // PA0
#define LED2 1  // PA1
#define LED3 2  // PA2
#define LED4 15 // PA15
#define LED5 8  // PA8
#define LED6 6  // PA6
#define LED7 5  // PA5
#define LED8 11 // PA11

// Display LCD
#define LCD_RS 15
#define LCD_EN 12

// Interruptores (Switches)
#define SW1 12  // PB12
#define SW2 13  // PB13
#define SW3 14  // PB14
#define SW4 15  // PB15
#define SW5 5   // PB5
#define SW6 4   // PB4
#define SW7 3   // PB3
#define SW8 3   // PA3
#define SW9 4   // PA4
#define SW10 8  // PB8
#define SW11 9  // PB9
#define SW12 11 // PB11
#define SW13 10 // PB10
#define SW14 7  // PA7
#define SW15 15 // PC15
#define SW16 14 // PC14
#define SW17 13 // PC13

// Potenciômetro
#define POT 1 // PB1

// Buzzer
#define BUZ 0 // PB0

/*----------------------------------------------------------------------------
  Declaração das funções
 *---------------------------------------------------------------------------*/
void setup_RedPill();
void led_Thread1(void const *argument);
void led_Thread2(void const *argument);
void led_Thread1(void const *argument);
void led_Thread2(void const *argument);

/*----------------------------------------------------------------------------
  Define os identificadores das threads e seus parâmetros
 *---------------------------------------------------------------------------*/
osThreadId T_led_ID1;
osThreadId T_led_ID2;
osThreadDef(led_Thread1, osPriorityNormal, 1, 0);
osThreadDef(led_Thread2, osPriorityNormal, 1, 0);

/*----------------------------------------------------------------------------
  Função principal
 *---------------------------------------------------------------------------*/
int main(void)
{
  osKernelInitialize(); // Inicializa o CMSIS-RTOS

  setup_RedPill(); // Configura os periféricos da RedPill

  T_led_ID2 = osThreadCreate(osThread(led_Thread2), NULL); // Cria a thread 2
  T_led_ID1 = osThreadCreate(osThread(led_Thread1), NULL); // Cria a thread 1

  osKernelStart(); // Inicia a execução das threads
  for (;;)
    ;
}

/*----------------------------------------------------------------------------
  Configuração inicial da RedPill
 *---------------------------------------------------------------------------*/
void setup_RedPill()
{
  // Habilita o relógio do AFIO
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
  osDelay(100);
  // Habilita os relógios para os GPIOs e o ADC1
  RCC->APB2ENR |= 0xFC | (1 << 9);
  ADC1->CR2 = 1;
  ADC1->CR2 |= (1 << 2);
  ADC1->SMPR2 = 1 << 3;
  osDelay(1);
  // Configura os pinos dos LEDs
  GPIOA->CRL = 0x43344333;
  GPIOA->CRH = 0x33333333;
  // Configuração dos pinos de entrada para os interruptores
  GPIOB->CRL = 0x4444440B;
  GPIOB->CRH = 0x44444444;
  GPIOB->ODR = 0xF000;
  GPIOC->CRH = 0x44444444;
  GPIOC->ODR = 0xFFFFFFFF;
  osDelay(1);
  GPIOA->ODR &= ~(1 << LCD_RS);
  osDelay(1);
}

/*----------------------------------------------------------------------------
  Pisca o LED 1 quando sinalizado pela led_Thread2
*---------------------------------------------------------------------------*/
void led_Thread1(void const *argument)
{
  for (;;)
  {
    osSignalWait(0x00, osWaitForever); // Espera até receber o sinal
    GPIOA->ODR |= (1 << LED1);         // Liga o LED 1
    osSignalWait(0x00, osWaitForever); // Espera novamente até o próximo sinal
    GPIOA->ODR &= ~(1 << LED1);        // Desliga o LED 1
		
		//5 - Sincronização de LED's
//		GPIOA->ODR |= (1 << LED1);         // Liga o LED 1
//		osSignalWait(0x01, osWaitForever); // Espera até receber o sinal
//    GPIOA->ODR &= ~(1 << LED1);        // Desliga o LED 1
//    osSignalWait(0x00, osWaitForever); // Espera novamente até o próximo sinal
  }
}

/*----------------------------------------------------------------------------
  Pisca o LED 2 e sincroniza o piscar do LED 1 definindo uma flag de sinal
*---------------------------------------------------------------------------*/
void led_Thread2(void const *argument)
{
  for (;;)
  {
    GPIOA->ODR |= (1 << LED2);    // Liga o LED 2
    osSignalSet(T_led_ID1, 0x01); // Define o sinal para a thread 1
    osDelay(500);                 // Atraso
    GPIOA->ODR &= ~(1 << LED2);   // Desliga o LED 2
    osSignalSet(T_led_ID1, 0x02); // Define o sinal para a thread 1
    osDelay(500);                 // Atraso
		//5 - Sincronização de LED's
//		GPIOA->ODR |= (1 << LED2);    // Liga o LED 2
//    osSignalSet(T_led_ID1, 0x01); // Define o sinal para a thread 1
//    osDelay(500);                 // Atraso
//    GPIOA->ODR &= ~(1 << LED2);   // Desliga o LED 2
//    osSignalSet(T_led_ID1, 0x01); // Define o sinal para a thread 1
//    osDelay(500);                 // Atraso
  }
}