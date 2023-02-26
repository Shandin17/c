/**
* @description в большинстве случаев нам не надо присваивать сокету конкретный ip-адрес
 * Когда нам нужен серверный сокет, проще проинструктировать систему принимать соединения
 * (или дейтаграммы) на заданный порт на любом из имеющихся в системе ip-адресов, а при отправке
 * исходящих дейтаграмм или запросов на установление соединения использовать ip-адрес
 * того сетевого интерфейса, через который происходит работа. Для этого поле
 * sin_addr следует заполнить специальным значением INADDR_ANY
 *
 * На самом деле INADDR_ANY - это просто арифм ноль (адрес 0.0.0.0)
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    /* ... */
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
   return 0;
}