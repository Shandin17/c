/**
* @description вызывается из клиентской программы. Отправляет запрос на соединение
* @args
 *      addr - структура, содержащая адрес сервера (адрес слушающего сокета)
 *      addrlen - размер этой структуры
*/
int connect(int sd, struct sockaddr *addr, int addrlen);