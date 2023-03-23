#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define INBUFSIZE 1024

/* ... */

enum fsm_states {
    fsm_start,
    fsm_name = fsm_start,
    fsm_age,
    fsm_town,
    fsm_band,
    fsm_finish,
    fsm_error
};

/**
 * Сеанс работы с клиентом можно описать структурой данных,
 * содержащей
 *  - дескриптор сокета
 *  - состояние автомата
 *  - накопительный буфер
 *  - поля для размещения сведений, полученных в ходе опроса
 *
 */
struct session {
    int fd; // socket descriptor
    enum fsm_states state; // state of the session
    char buf[INBUFSIZE]; // buffer
    int buf_used; // amount of data in buffer
    char *name, *town, *band; // received data
    int age;
};

void session_send_string(struct session *sess, const char *str);
void session_check_lf(struct session *sess);

/* Инициализацию сеанса, то есть действия, выполняемые сразу после вызова accept,
 * можно совместить с созданием в динамической памяти экземпляра структуры session
 *
 * Также включим в инициализацию отправку клиенту первого вопроса
 */
struct session *make_new_session(int fd) {
    struct session *sess = malloc(sizeof(*sess));
    sess->fd = fd;
    sess->buf_used = 0;
    sess->state = fsm_start;
    sess->name = NULL;
    sess->town = NULL;
    sess->band = NULL;
    sess->age = -1;
    session_send_string(sess, "What is your name?\n");
    return sess;
}

void session_send_string(struct session *sess, const char *str) {
    write(sess->fd, str, strlen(str));
}

/**
 * вспомогательная функция для обработки ответа о возрасте
 */
 void session_handle_age(struct session *sess, const char *line) {
     char *err;
     int age;
     age = strtol(line, &err, 10);
     if (!*line || *err || age < 0 || age > 150) {
         session_send_string(sess, "Please try again!\n");
         session_send_string(sess, "How old are you?\n");
     } else {
         sess->age = age;
         session_send_string(sess, "What city/town are you from?\n");
         sess->state = fsm_town;
     }
 }

/**
 * шаг автомата
 */
void session_fsm_step(struct session *sess, char *line) {
    switch (sess->state) {
        case fsm_name:
            sess->name = line;
            session_send_string(sess, "How old are you?\n");
            sess->state = fsm_age;
            break;
        case fsm_age:
            session_handle_age(sess, line);
            break;
        case fsm_town:
            sess->town = line;
            session_send_string(sess, "What is your favorite band?\n");
            sess->state = fsm_band;
            break;
        case fsm_band:
            sess->band = line;
            session_send_string(sess, "Thank you, bye!\n");
            sess->state = fsm_finish;
            break;
        case fsm_finish:
        case fsm_error:
            free(line); // should never happen;
    }
}

/**
 * функция, выполняющая чтение из сокета в накопительный буфер
 * Возвращает 1 если сеанс работы еще не завершен и должен продолжаться
 * Возвращает 0 если продолжение работы с сеансом не требуется
 *
 * Когда мы получим от вызова select информацию о готовности сокета к чтению, главный
 * цикл должен вызвать (напрямую или как-либо косвенно) функцию session_do_read, которая будет производить
 * чтение из сокета в накопительный буфер
 *
 * В свою очередь session_do_read, выполнив чтение, дальнейшие действия - проверку, пришла ли строка,
 * и вызов шага автомата - возложит на следующую функцию - session_check_lf (lf - line feed - символ
 * перевода строки). Заодно (уже после возможного изъятия из буфера очередной строки) функция проверит,
 * не переполнился ли накопительный буфер, а затем - не перешел ли автомат в заключительное состояние.
 */
int session_do_read(struct session *sess) {
    int rc, bufp = sess->buf_used;
    rc = read(sess->fd, sess->buf + bufp, INBUFSIZE - bufp);
    if (rc <= 0) {
        sess->state = fsm_error;
        return 0;
    }
    sess->buf_used += rc;
    session_check_lf(sess);
    if (sess->buf_used >= INBUFSIZE) {
        // buffer is full
        session_send_string(sess, "Line too long! Bye ... \n");
        sess->state = fsm_error;
        return 0;
    }
    if (sess->state == fsm_finish) {
        return 0;
    }
    return 1;
}

/**
* Функция session_check_lf должна связать между собой
 * "системную" обвеску и "прикладной" автомат.
 *
 * Для этого она попытается найти в "занятой" части
 * накопительного буфера символ перевода строки;
 * Если этого символа там нет, то она просто вернет
 * управление в надежде что в след раз он появится
 * Если перевод строки в буфере найдется, функция создаст
 * копию данных из буфера (от начала до перевода строки) в виде
 * отдельной строки памяти, причем эта строка не будет включать
 * символ перевода строки.
 * Данные в буфере будут сдвинуты к началу, чтобы затереть изъятую
 * строку, а саму эту строку функция передаст в session_fnm_step
 *
 * В качестве последнего штриха, сделаем проверку на символ
 * возврата каретки '\r и заменим его на нулевой байт
*/
void session_check_lf(struct session *sess) {
    int pos = -1;
    int i;
    char *line;
    for (i = 0; i < sess->buf_used; i++) {
        if (sess->buf[i] == '\n') {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        return;
    }
    line = malloc(pos + 1);
    memcpy(line, sess->buf, pos);
    line[pos] = 0;
    sess->buf_used -= (pos + 1);
    memmove(sess->buf, sess->buf + pos + 1, sess->buf_used);
    if (line[pos - 1] == '\r') {
        line[pos - 1] = 0;
    }
    session_fsm_step(sess, line);
}