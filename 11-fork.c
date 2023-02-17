/**
* @bullet системный вызов: порождение процесса
* @description создает процесс копируя текущий
* @return -1 если возникает ошибка
 * 0 в порожденном процессе
 * pid в старом процесса (pid порожденного процесса)
*/
int fork(void);

#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("Hello!\n"); // 8 times
}