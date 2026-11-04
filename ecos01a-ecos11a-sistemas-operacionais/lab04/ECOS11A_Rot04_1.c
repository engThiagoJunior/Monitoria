#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Processo filho
        printf("Processo filho: PID = %d, PID do pai = %d\n", getpid(), getppid());
    } else if (pid > 0) {
        // Processo pai
        printf("Processo pai: PID = %d, PID do filho = %d\n", getpid(), pid);
    } else {
        // Falha ao criar processo filho
        fprintf(stderr, "Falha ao criar processo filho\n");
        return 1;
    }

    return 0;
}
