#ifndef DRIVERS_H
#define DRIVERS_H

#include <stdio.h>
#include <stdlib.h>

// Definindo o tipo de ponteiro para função que aceita um parâmetro void
typedef void (*ptrFunc)(void*);

// Definindo os tipos de drivers usando enum
typedef enum {
    gen = 0,    // Driver Genérico
    inti = 1,   // Driver de Interrupção
    tim = 2     // Driver de Timer
} Type;

// Estrutura de um driver
typedef struct driver {
    char id;                // Identificador do driver
    ptrFunc initFunc;       // Função de inicialização do driver
    ptrFunc* funcoes;       // Array de ponteiros para funções do driver
    size_t funcCount;       // Contagem de funções associadas ao driver
} driver;

// Funções para obter os drivers (com as funções associadas)
struct driver* getGenericoDriver(void);
struct driver* getInterruptDriver(void);
struct driver* getTimerDriver(void);

// Funções do controlador de drivers
char initCtrDrv(void);
char initDriver(char newDriver);
char callDriver(char drv_id, char func_id, void *parameters);
void adiciona(Type typedriver, ptrFunc newfunc);
void ExecutDriver(char drv_id, void *parameters);

#endif // DRIVERS_H