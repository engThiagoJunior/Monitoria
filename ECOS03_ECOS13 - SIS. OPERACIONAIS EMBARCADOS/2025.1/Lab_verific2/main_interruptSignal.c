#include "stm32f10x.h"
#include "cmsis_os.h"
#include "Board_LED.h"

/*----------------------------------------------------------------------------
  Declaração das funções
 *---------------------------------------------------------------------------*/
void led_Thread1 (void const *argument);
void led_Thread2 (void const *argument);
void adc_Thread  (void const *argument);
void init_ADC (void);						

/*----------------------------------------------------------------------------
  Define os identificadores das threads e seus parâmetros
 *---------------------------------------------------------------------------*/
osThreadId T_led_ID1;
osThreadId T_led_ID2;	
osThreadId T_adc_ID;
osThreadDef(led_Thread1, osPriorityNormal, 1, 0);
osThreadDef(led_Thread2, osPriorityNormal, 1, 0);
osThreadDef(adc_Thread, osPriorityAboveNormal, 1, 0);

/*----------------------------------------------------------------------------
  Função principal
 *---------------------------------------------------------------------------*/
int main (void) {
    LED_Initialize();        // Inicializa os LEDs
    init_ADC();              // Inicializa o ADC
    T_led_ID1 = osThreadCreate(osThread(led_Thread1), NULL);  // Cria a thread 1
    T_led_ID2 = osThreadCreate(osThread(led_Thread2), NULL);  // Cria a thread 2
    T_adc_ID = osThreadCreate(osThread(adc_Thread), NULL);    // Cria a thread ADC

    for (;;);
}

/*----------------------------------------------------------------------------
  Inicialização do ADC, configurando o clock e os parâmetros necessários
  A função é definida como SVC (SuperVisor Call) e precisa ser executada em modo privilegiado
 *---------------------------------------------------------------------------*/
void init_ADC(void) {
    RCC->APB2ENR |= (1UL << 2);           // Habilita o clock para o GPIOA
    GPIOA->CRL &= ~0x000000F0;            // Configura o pino 1 como entrada analógica

    // Configuração e inicialização do conversor ADC
    RCC->CFGR |= (3UL << 14);             // Configura o clock do ADC: PCLK2 / 8
    RCC->APB2ENR |= (1UL << 9);           // Habilita o clock para o ADC1

    ADC1->SQR1 = 0;                       // Tamanho da sequência de canais regular = 1
    ADC1->SQR2 = 0;                       // Limpa o registro
    ADC1->SQR3 = (1UL << 0);              // 1ª conversão = canal 1
    ADC1->SMPR2 = (5UL << 3);             // Tempo de amostragem do canal 1: 55,5 ciclos
    ADC1->CR1 = (1UL << 8);               // Habilita o modo de varredura
    ADC1->CR2 = (7UL << 17) |             // Seleciona o trigger de SWSTART
                (1UL << 20);              // Habilita o trigger externo

    ADC1->CR1 |= (1UL << 5);              // Habilita a interrupção para o fim de conversão (EOC)
    NVIC->ISER[0] = (1UL << 18);          // Habilita a interrupção do ADC no NVIC (deve estar em modo privilegiado)
}

/*----------------------------------------------------------------------------
  Manipulador de interrupção do ADC. Quando a conversão termina, define o sinal da thread ADC.
 *---------------------------------------------------------------------------*/
void ADC1_2_IRQHandler (void)
{
    osSignalSet(T_adc_ID, 0x01);   // Define o sinal para a thread ADC
    ADC1->SR &= ~(1 << 1);         // Limpa a flag de interrupção do ADC
}

/*----------------------------------------------------------------------------
  Função da thread que manipula a leitura do ADC e exibe o valor no GPIOB.
 *---------------------------------------------------------------------------*/
void adc_Thread (void const *argument)
{
    for (;;) 
    {	
        osSignalWait(0x01, osWaitForever);  // Espera o sinal de interrupção do ADC
        GPIOB->ODR = ADC1->DR;             // Lê o valor do ADC e coloca no GPIOB
    }	
}

/*----------------------------------------------------------------------------
  Função da thread que pisca o LED 1 quando recebe o sinal da thread led_Thread2
 *---------------------------------------------------------------------------*/
void led_Thread1 (void const *argument) 
{
    for (;;)
    {
        osSignalWait(0x01, osWaitForever);  // Espera até receber o sinal
        LED_On(1);                           // Liga o LED 1
        osSignalWait(0x01, osWaitForever);  // Espera novamente até o próximo sinal
        LED_Off(1);                          // Desliga o LED 1
    }
}

/*----------------------------------------------------------------------------
  Função da thread que controla o LED 2 e sincroniza com o LED 1 via sinais.
  Inicia a conversão do ADC quando o LED 2 é desligado.
 *---------------------------------------------------------------------------*/
void led_Thread2 (void const *argument) 
{
    for (;;) 
    {
        LED_On(2);                        // Liga o LED 2
        osSignalSet(T_led_ID1, 0x01);     // Define o sinal para a thread led_Thread1
        osDelay(500);                     // Aguarda 500 ms
        ADC1->CR2 |=  (1UL << 22);        // Inicia a conversão do ADC
        LED_Off(2);                       // Desliga o LED 2
        osSignalSet(T_led_ID1, 0x01);     // Define o sinal para a thread led_Thread1
        osDelay(500);                     // Aguarda 500 ms
    }
}