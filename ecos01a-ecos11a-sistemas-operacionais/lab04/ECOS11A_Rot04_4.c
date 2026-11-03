#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() {
    int ret;
    printf("Ajustando a prioridade do processo atual...\n");

    // Aumenta a "nice value" do processo, diminuindo sua prioridade
    ret = nice(5);
    if (ret == -1) {
        perror("nice");
        return 1;
    }

    // Executa uma tarefa
    for (int i = 0; i < 1000000; i++) {
        // Tarefa fictícia para manter o processo ocupado
    }

    printf("Prioridade do processo ajustada.\n");
    return 0;
}
