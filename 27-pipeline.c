// конвейер: ls -lR | grep '^d'
// реализация на Си с помощью неименованного канала
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd); // создаем канал связи
    if (fork() == 0) { // процесс для выполнения ls -lR
        close(fd[0]); // читать из канала не нужно
        dup2(fd[1], 1); // переназначаем стандартный вывод на канал (под единицей теперь канал)
        close(fd[1]); // закрываем fd[1] (этот объект теперь под единицей)
        execlp("ls", "ls", "-lR", NULL);
        perror("ls"); // сообщение об ошибке
        exit(1);
    }

    if (fork() == 0) { // процесс для выполнения grep
        close(fd[1]);
        dup2(fd[0], 0); //стандартный ввод теперь канал
        close(fd[0]);
        execlp("grep", "grep", "^d", NULL);
        perror("grep");
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}