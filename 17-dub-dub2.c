#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/**
* @description создает новый файловый дескриптор, связанный с тем же самым
 *      потоком ввода-вывода, что и fd.
 *      Нового протока при этом не создается, оба дескриптора связаны с одним и тем же
 *      объектом ядра
* @args
 *  fd - тот дескр который нужно скопировать
* @return
 * дескриптор
 *
*/
int dup(int fd);


/**
* @description копирует то что лежит под fd в new_fd
 * при этом то что лежало под new_fd раньше - уничтожается
 *
*/
int dup2(int fd, int new_fd);


void print_system_info() {
    int pid, status;
    pid = fork();
    if (pid == 0) { // порожденный процесс
        int fd = open("flist", O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if (fd == -1) {
            perror("flist");
            exit(1);
        }
        dup2(fd, 1); // скопировали fd в единицу (теперь это стандартный поток вывода)
        close(fd); //этот больше не нужен, у нас под номером 1 лежит тот же объект теперь
        execlp("ls", "ls", "-l", "-a", "-R", "/", NULL);
        perror("ls");
        exit(1); //закрываем порожденный процесс
    }
    wait(&status); // ждем завершения порожденного процесса
}

int main() {
    print_system_info();
    return 0;
}