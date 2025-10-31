#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef int (*ptrFunc)(void);

typedef struct {
    char * name;
    int time;
    ptrFunc func;
}process;

#define BUFFERSIZE  10
process buffer[BUFFERSIZE];

int start=0, end=0;

void addProc(process newProcess) {
    if (((end + 1) % BUFFERSIZE) != start) {
        buffer[end].name = strdup(newProcess.name); // Cópia do nome
        buffer[end].time = newProcess.time;
        buffer[end].func = newProcess.func;
        end = (end + 1) % BUFFERSIZE;
    } else {
        printf("Buffer cheio, processo %s não adicionado.\n", newProcess.name);
    }
}

void removeProc (void){
  if (start != end){
    buffer[start].func();
    start = (start +1)%(BUFFERSIZE);
  }
}

int func1(void) { printf("Executando func1\n"); return 0; }
int func2(void) { printf("Executando func2\n"); return 0;}
int func3(void) { printf("Executando func3\n"); return 0;}

void main (void){
  process p1 = {"Processo 1", 1, func1};
  process p2 = {"Processo 2", 2, func2};
  process p3 = {"Processo 3", 3, func3};

  addProc(p1);
  addProc(p2);
  addProc(p3);

  removeProc();
  removeProc();
  removeProc();

}




