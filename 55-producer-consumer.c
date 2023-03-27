// pseudocode

void producer() {
    /*
     * preparing data ...
     */
    down(empty); // will block producer if empty == 0
    lock(m);
    put_data();
    unlock(m);
    up(full);
}

void consumer() {
    down(full); // will block consumer if full == 0
    lock(m);
    get_data();
    unlock(m);
    up(empty);
    /*
     * handle data
     */
}

