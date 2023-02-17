#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    if (pid == -1) { // ошибка порождения процесса
        perror("fork"); // выводит сообщение в стандартный поток диагностики, куда параметром передается
            // строка описывающая, что произошло
        exit(1);
    }

    if (pid == 0) { // порожденный процесс
        execlp("ls", "ls", "-l", "-a", "/var", NULL);
        perror("ls");
        exit(1);
    }

    // родительский процесс
    // int wait(int *status); вернет pid, в status положит код завершения процесса (или номер сигнала)
    wait(NULL); // ждет завершения порожденного процесса (любого первого)
    printf("Ok\n");
    return 0;
}