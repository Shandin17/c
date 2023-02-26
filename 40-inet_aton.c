/**
* @description преобразует ip адрес "192.168.10.12" в структуру struct in_addr (структура имеет
 * только одно поле - адрес)
 * @args
 *      cp - строка, содержащая текстовое представление ip-адреса
 *      inp - структура подлежащая заполнению
 * @return
 *  0 - НЕДОПУСТИМАЯ текстовая запись айпи адреса
 *  любое другое число - допустимая
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int inet_aton(const char *cp, struct in_addr *inp);


//example
void fill_sockaddr_in(struct sockaddr_in *addr, char *serv_ip, short port) {
    int ok;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    ok = inet_aton(serv_ip, &(addr->sin_addr));
    // есть еще функция unsigned int inet_addr(const char *cp)
    // она вернет адрес уже в сетевом порядке байтов
    // этот адрес можно положить в sin_addr.s_addr
    if (!ok) {
        // ошибка - невалидный ip-адрес
    }
}



