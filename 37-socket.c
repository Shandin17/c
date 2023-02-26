/**
 * @description создает сокет
 * @args
 *      family - задает используемое семейство адресации
 *          AF_INET - TCP/IP (адрес сокета в этом случае пара ip/port)
 *          AF_UNIX - взаимодействие в рамках одной машины (адрес сокета - имя файла)
 *     type - задает тип взаимодействия
 *          SOCK_STREAM - потоковое взаимодействие
 *          SOCK_DGRAM - дейтограммному
 *     protocol - конкретный используемый протокол
 * @return
 *      -1 в случае ошибки
 *      в случае успеха возвращает номер файлового дескриптора, связанного с созданным сокетом
 */
int socket(int family, int type, int protocol)