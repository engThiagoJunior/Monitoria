#include <stdio.h>
#include <stdlib.h>
#include "ECOS13_Lab03_drivers.h"

#define QNTD_DRV 20
#define DRV_FUNC_NOT_FOUND -1
#define SUCCESS 0
#define FAIL -1
#define RETORNA 0  // Número de vezes que a Funcao será executada

#define MAX_FUNC_COUNT 10  // Define o tamanho máximo do buffer circular para funções

// Definindo os buffers circulares para cada tipo de driver
ptrFunc genFunc[MAX_FUNC_COUNT];
ptrFunc intFunc[MAX_FUNC_COUNT];
ptrFunc timFunc[MAX_FUNC_COUNT];

// Inicializando os drivers
void initGenericoDriver(void *param) { printf("[INFO] Driver de Generico inicializado.\n"); }
void func1GenericoDriver(void *param) { printf("[INFO] Driver de Generico - Funcao 1 executada.\n"); }
void func2GenericoDriver(void *param) { printf("[INFO] Driver de Generico - Funcao 2 executada.\n"); }
void func3GenericoDriver(void *param) { printf("[INFO] Driver de Generico - Funcao 3 executada.\n"); }

void initInterruptDriver(void *param) { printf("[INFO] Driver de Interrupcao inicializado.\n"); }
void func1InterruptDriver(void *param) { printf("[INFO] Driver de Interrupcao - Funcao 1 executada.\n"); }
void func2InterruptDriver(void *param) { printf("[INFO] Driver de Interrupcao - Funcao 2 executada.\n"); }
void func3InterruptDriver(void *param) { printf("[INFO] Driver de Interrupcao - Funcao 3 executada.\n"); }

void initTimerDriver(void *param) { printf("[INFO] Driver de Timer inicializado.\n"); }
void func1TimerDriver(void *param) { printf("[INFO] Driver de Timer - Funcao 1 executada.\n"); }
void func2TimerDriver(void *param) { printf("[INFO] Driver de Timer - Funcao 2 executada.\n"); }
void func3TimerDriver(void *param) { printf("[INFO] Driver de Timer - Funcao 3 executada.\n"); }

// Definindo os índices dos buffers circulares
int genFuncIndex = 0;
int intFuncIndex = 0;
int timFuncIndex = 0;

// Definindo os drivers carregados
static driver* drivers[QNTD_DRV];
static char dLoaded = 0;

struct driver* getGenericoDriver(void) {
    struct driver* genDriver = malloc(sizeof(struct driver));
    if (genDriver == NULL) {
        printf("[ERROR] Erro ao alocar memoria para o driver Generico.\n");
        return NULL;
    }

    genDriver->id = gen;
    genDriver->initFunc = initGenericoDriver;
    genDriver->funcoes = genFunc;
    genDriver->funcCount = 3;  // Inicializa com 3 funções
    return genDriver;
}

struct driver* getInterruptDriver(void) {
    struct driver* intDriver = malloc(sizeof(struct driver));
    if (intDriver == NULL) {
        printf("[ERROR] Erro ao alocar memoria para o driver de Interrupcao.\n");
        return NULL;
    }

    intDriver->id = inti;
    intDriver->initFunc = initInterruptDriver;
    intDriver->funcoes = intFunc;
    intDriver->funcCount = 3;  // Inicializa com 3 funções
    return intDriver;
}

struct driver* getTimerDriver(void) {
    struct driver* timeDriver = malloc(sizeof(struct driver));
    if (timeDriver == NULL) {
        printf("[ERROR] Erro ao alocar memoria para o driver de Timer.\n");
        return NULL;
    }

    timeDriver->id = tim;
    timeDriver->initFunc = initTimerDriver;
    timeDriver->funcoes = timFunc;
    timeDriver->funcCount = 3;  // Inicializa com 3 funções
    return timeDriver;
}

// Funcao para adicionar uma Funcao a um driver específico
void adiciona(Type typedriver, ptrFunc newfunc) {
    switch (typedriver) {
        case gen:
            genFunc[genFuncIndex] = newfunc;
            genFuncIndex = (genFuncIndex + 1) % MAX_FUNC_COUNT;  // Incrementa o índice circular
            drivers[gen]->funcCount++;  // Atualiza a contagem de funções
            printf("[INFO] Funcao adicionada ao driver Generico.\n");
            break;

        case inti:
            intFunc[intFuncIndex] = newfunc;
            intFuncIndex = (intFuncIndex + 1) % MAX_FUNC_COUNT;  // Incrementa o índice circular
            drivers[inti]->funcCount++;  // Atualiza a contagem de funções
            printf("[INFO] Funcao adicionada ao driver de Interrupcao.\n");
            break;

        case tim:
            timFunc[timFuncIndex] = newfunc;
            timFuncIndex = (timFuncIndex + 1) % MAX_FUNC_COUNT;  // Incrementa o índice circular
            drivers[tim]->funcCount++;  // Atualiza a contagem de funções
            printf("[INFO] Funcao adicionada ao driver de Timer.\n");
            break;
    }
}

// Funções do controlador de drivers
char initCtrDrv(void) {
    dLoaded = 0;
    return SUCCESS;
}

// Função para inicializar drivers
char initDriver(char newDriver) {
    char resp = FAIL;

    if (dLoaded < QNTD_DRV) {
        switch (newDriver) {
            case gen: 
                drivers[dLoaded] = getGenericoDriver(); 
                drivers[dLoaded]->initFunc(NULL); // Chama a função de inicialização do driver genérico
                break;
            case inti: 
                drivers[dLoaded] = getInterruptDriver(); 
                drivers[dLoaded]->initFunc(NULL); // Chama a função de inicialização do driver de interrupção
                break;
            case tim: 
                drivers[dLoaded] = getTimerDriver(); 
                drivers[dLoaded]->initFunc(NULL); // Chama a função de inicialização do driver de timer
                break;
            default: 
                return FAIL;
        }
        resp = SUCCESS;
        dLoaded++;
    }
    return resp;
}

// Funcao para verificar e executar funções do driver
char callDriver(char drv_id, char func_id, void *parameters) {
    int num_rep = RETORNA;  // Define o número de repetições
    for (char i = 0; i < dLoaded; i++) {
        if (drv_id == drivers[i]->id) {
            // Verificação para garantir que func_id está dentro dos limites
            if (func_id < 0 || func_id >= drivers[i]->funcCount) {
                printf("[ERROR] func_id %d fora dos limites para o driver %d.\n", func_id, drv_id);
                return DRV_FUNC_NOT_FOUND;
            }
            
            // Executa a Funcao `num_rep` vezes
            do {
                printf("[INFO] Chamando Funcao %d do driver %d.\n", func_id, drv_id);
                drivers[i]->funcoes[func_id](parameters);
                num_rep--;
            } while (num_rep == 0);  // Correção do laço para repetir enquanto num_rep for maior que 0
            return SUCCESS;
        }
    }
    return DRV_FUNC_NOT_FOUND;
}

// Funcao para executar todas as funções de um driver
void ExecutDriver(char drv_id, void *parameters) {
    for (int i = 0; i < dLoaded; i++) {
        if (drv_id == drivers[i]->id) {
            for (int j = 0; j < drivers[i]->funcCount; j++) {
                printf("[INFO] Chamando Funcao %d do driver %d...\n", j, drv_id);
                drivers[i]->funcoes[j](parameters);
            }
        }
    }
}

// Funcao principal (main)
int main(void) {
    initCtrDrv();
    initDriver(gen);  // Driver Generico
    initDriver(inti); // Driver de Interrupcao
    initDriver(tim);  // Driver de Timer

    // Adicionando funções aos drivers
    adiciona(gen, func1GenericoDriver);
    adiciona(gen, func2GenericoDriver);
    adiciona(gen, func3GenericoDriver);

    adiciona(inti, func1InterruptDriver);
    adiciona(inti, func2InterruptDriver);
    adiciona(inti, func3InterruptDriver);

    adiciona(tim, func1TimerDriver);
    adiciona(tim, func2TimerDriver);
    adiciona(tim, func3TimerDriver);

    // Chamando funções de exemplo
    callDriver(gen, 1, NULL);
    callDriver(inti, 2, NULL);

    // Executando todas as funções de todos os drivers
    ExecutDriver(gen, NULL);    // Chama todas as funções do driver Generico
    ExecutDriver(inti, NULL);   // Chama todas as funções do driver de Interrupcao
    ExecutDriver(tim, NULL);    // Chama todas as funções do driver de timer

    return 0;
}