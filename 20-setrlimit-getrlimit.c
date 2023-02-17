/**
* @description установка количественных ограниченичений на процесс
* @args
 * rlimit { rlim_cur, rlim_max } - мягкий и жесткий уровень соотв (int оба)
        указывается RLIM_INFINITY если ограничения не предусмотрено
 * resource - указывает какое именно граничение следует установить (изменить)
        RLIMIT_AS - максимальное количество вирт памяти для отдельно взятого процесса
        ну и другие там есть (man 2 setrlimit)

*/
int setrlimit(int resource, const struct rlimit *rlim);

/**
* @description узнать текущие ограниченя процесса
*/
int getrlimit(int resource, struct rlimit *rlim);