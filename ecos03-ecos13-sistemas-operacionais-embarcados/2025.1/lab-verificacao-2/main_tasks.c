#include "STM32F10x.h"
#include <cmsis_os.h>
#include "Board_LED.h"

/*----------------------------------------------------------------------------
  Declaração das funções
 *---------------------------------------------------------------------------*/
void delay(unsigned int count);
void led_thread1(void const *argument);
void led_thread2(void const *argument);
void ledSwitcher(void const *argument);
void ledOn(void const *argument);
void ledOff(void const *argument);

/*----------------------------------------------------------------------------
  Definição das threads e parâmetros
 *---------------------------------------------------------------------------*/
osThreadId main_ID, led_ID1, led_ID2;

// 2 - GERENCIAMENTO DE THREADS
osThreadDef(led_thread1, osPriorityNormal, 1, 0);
osThreadDef(led_thread2, osPriorityNormal, 1, 0);

// 3 - MULTIPLAS INSTÂNCIAS
osThreadDef(ledSwitcher, osPriorityAboveNormal, 2, 0);

// 5 - GESTÃO DE TEMPO
osThreadDef(ledOff, osPriorityNormal, 1, 0);
osThreadDef(ledOn, osPriorityNormal, 1, 0);

/*----------------------------------------------------------------------------
  Função principal
 *---------------------------------------------------------------------------*/
int main(void)
{
    osKernelInitialize(); // Inicializa o CMSIS-RTOS

    LED_Initialize(); // Inicializa o sistema de LEDs

    // Cria as threads para os LEDs
    // 2 - GERENCIAMENTO DE THREADS
    led_ID1 = osThreadCreate(osThread(led_thread1), NULL);
    led_ID2 = osThreadCreate(osThread(led_thread2), NULL);
    // 3 - MULTIPLAS INSTÂNCIAS
    //led_ID1 = osThreadCreate(osThread(ledSwitcher), (void *)1UL); // Cria a primeira instância da função ledSwitcher
    //led_ID2 = osThreadCreate(osThread(ledSwitcher), (void *)2UL); // Cria a segunda instância da função ledSwitcher
    //5 - GESTÃO DE TEMPO
    //osThreadCreate(osThread(ledOff), NULL); // Cria a thread para desligar o LED
    //osThreadCreate(osThread(ledOn), NULL);  // Cria a thread para ligar o LED

    osKernelStart(); // Inicia a execução das threads

    while (1)
    {
        ; // Loop infinito
    }
}

/*----------------------------------------------------------------------------
  Função de atraso simples
 *---------------------------------------------------------------------------*/
void delay(unsigned int count)
{
    unsigned int index;

    for (index = 0; index < count; index++)
    {
        ;
    }
}

/*----------------------------------------------------------------------------
  Pisca o LED 1
 *---------------------------------------------------------------------------*/
void led_thread1(void const *argument)
{
    for (;;)
    {
        LED_On(1);  // Liga o LED 1
        delay(500); // Aguarda 500 ciclos
        LED_Off(1); // Desliga o LED 1
        delay(500); // Aguarda 500 ciclos
    }
}

/*----------------------------------------------------------------------------
  Pisca o LED 2
 *---------------------------------------------------------------------------*/
void led_thread2(void const *argument)
{
    for (;;)
    {
        LED_On(2);  // Liga o LED 2
        delay(500); // Aguarda 500 ciclos
        LED_Off(2); // Desliga o LED 2
        delay(500); // Aguarda 500 ciclos
    }
}

/*----------------------------------------------------------------------------
  Função de thread para alternar o LED
 *---------------------------------------------------------------------------*/
void ledSwitcher(void const *argument)
{
    for (;;)
    {
        LED_On((uint32_t)argument);  // Liga o LED indicado pelo argumento
        delay(500);                  // Atraso de 500 ciclos
        LED_Off((uint32_t)argument); // Desliga o LED indicado pelo argumento
        delay(500);                  // Atraso de 500 ciclos
    }
}

/*----------------------------------------------------------------------------
  Tarefa 1 'ledOn': liga o LED
 *---------------------------------------------------------------------------*/
void ledOn(void const *argument)
{
    for (;;)
    {
        LED_On(1);    // Liga o LED 1 com um atraso de 500 ms
        osDelay(500); // Atraso de 500 ms
        LED_Off(1);   // Desliga o LED 1
        osDelay(500); // Atraso de 500 ms
    }
}

/*----------------------------------------------------------------------------
  Tarefa 2 'ledOff': desliga o LED
 *---------------------------------------------------------------------------*/
void ledOff(void const *argument)
{
    for (;;)
    {
        LED_On(2);    // Liga o LED 2 com um atraso de 100 ms
        osDelay(100); // Atraso de 100 ms
        LED_Off(2);   // Desliga o LED 2
        osDelay(100); // Atraso de 100 ms
    }
}