/**
* @description создает именнованный канал (FIFO)
 * @args
 *      name - имя файла
 *      permissions - права доступа к нему
 * @return
 *      -1 - ошибка
 *      0 - успех
*/
int mkfifo(const char *name, int permissions);