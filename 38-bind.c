/**
 * @description снабжает сокет адресом
 * @args
 *      sockfd - дескриптор сокета, полученный в результате выполнения вызова socket
 *      addr - указатель на структуру, содержащую адрес
 *          в реальности, в семействе AF_INET используется структура struct sockaddr_in
 *          sockaddr_in:
 *              sin_family - семейство адресации
 *              sin_port - порт в СЕТЕВОМ порядке байтов (может отличаться от того, который уст на машине)
 *              sin_addr - беззнаковое целое число в сетевой порядке байтов
 *      addrlen - размер структуры адреса в байтах
 * @return
 *      0 и -1
 */
int bind(int sockfd, struct sockaddr *addr, int addrlen);

// часто тип структуры явно приводят так:
res = bind(sd, (struct sockaddr*)&addr, sizeof(addr));