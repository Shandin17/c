/**
* @description создает неименованный канал
* @args fd[2] - в этот массив pipe записывается дескрипторы
 * fd[0] - для чтения
 * fd[1] - для записи
 * @return -1 - в случае ошибки
*/
int pipe(int fd[2]);