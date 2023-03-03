/**
* @description обеспечивает принятие соединения
 * @dev
 *      sd - дескриптор слушающего сокета.
 *      addr - указывает на структуру для записи адреса сокета, с которым установлено соединение
 *          (иначе говоря, сюда будет записан адрес другого конца соединения).
 *      addrlen - адрес переменной типа socklen_t. Перед вызовом accept сюда надо занести
 *          размер адресной структуры, на которую указывает предыдущий параметр;
 *          после возврата переменная будет содержать колво байт, которое вызов в итоге в эту структуру
 *          записал
 * @return файловый дескриптор нового сокета, созданного для обслуживания установленного соединения
 *
 *
*/
int accept(int sd, struct sockaddr *addr, socklen_t *addrlen);