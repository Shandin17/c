/**
* @description создает новый сеанс
 *      Вызов не пройдет, если данный процесс уже является лидером сеанса или хотя бы группы
 *      Чтобы гарантировать успешное создание сеанса, следует вызвать fork()
 *      и завершить родительский процесс, сменив, таким образом, свой pid
*/
int setsid();

// good practice:
pid = fork();
if (pid > 0) {
    exit(0);
}
setsid();

/**
 * @description смена группы
 *      Группу можно менять либо на уже существующую в рамках сеанса, либо
 *      можно задать параметр pgid равный pid, в этом случае создается новая группа,
 *      а процесс становится ее лидером
 * @arg
 *      pid - номер процесса, который нужно перевести в другую группу
 *      pgid - номер этой группы
 */
int setpgid(int pid, int pgid);
