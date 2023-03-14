#include <sys/select.h>

/**
 * В событийно-ориентированных программах тело главного (бесконечного)
 *  цикла делится на две фазы - ВЫБОРКУ события и ОБРАБОТКУ события
 *  В данном схематическом примере фаза ВЫБОРКИ заканчивается вызовом select, а все
 *  остальное до конца цикла - это обработка полученного события
 *
 *  Предполагается что номер слушающего сокета хранится в переменной ls
 *
 *  Организовать хранение дескрипторов клиентских сокетов можно кучей способов (деревом, массивом ...)
 *
 *  Предполагаем что out-of-band data не используется, так что параметр exfds оставлен нулевым, как
 *  и параметр timeout
 */

// Main cycle
for (;;) {
    int fd, res;
    fd_set readfds, writefds;
    int max_d = ls; // assume that listen socket got a max number
    FD_ZERO(&readfds); // clean set
    FD_ZERO(&writefds); // clean set
    FD_SET(ls, &readfds); //add ls to read set

    for (
            fd = /* descriptor of first socket */ ;
            /* sockets remained? */ ;
            fd = /* socket of next client */
        ) {
        /* fd - client descriptor */
        /* add fd to set */
        FD_SET(fd, &readfds);
        if (/* is there any data for client? */) {
            FD_SET(fd, &writefds);
            /* check if fd > max_d */
            if (fd > max_d) max_d = fd;

        }
        timeout.tv_sec = /* fill */;
        timeout.tv_usec = /* timeout */;

        res = select(max_d + 1, &readfds, &writefds, NULL, NULL);
        if (res == -1) {
            if (errno == EINTR) {
                /* обработка события "пришедший сигнал" */
            } else {
                /* обработка ошибки, происшедшей в select'е */
            };
            continue;
        }
        if (res == 0) {
            /* обработка события "тайм-аут" */
            continue;
        }
        if(FD_ISSET(ls, &readfds)) {
            /* пришел новый запрос на соединение */
            /*
             * здесь его надо принять вызовом accept
             * и запомнить дескриптор нового клиента;
             * кроме того, не забудем про перевод сокета в неблокирующий режим
             * с помощью fcntl, если используем writefds
             */
        }

        /* теперь перебираем все клиентские дескрипторы */
        for (
                fd = /* дескриптор первого клиента */;
                /* клиенты еще не исчерпаны? */;
                fd = /* дескриптор следующего клиента */
        ) {
            if (FD_ISSET(fd, &readfds)) {
                /* пришли данные от клиента с сокетом fd */
                /* читаем их вызовом read или recv и обрабатываем */
            }
            if (FD_ISSET(fd, &writefds)) {
                /* готовность на запись: пробуем отправить очередную порцию данных */
            }
            /* конец главного цикла */
        }
    }
}