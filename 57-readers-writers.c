// pseudocode

/**
 * db_access - binary semaphore (
 * using semaphore because we dont need access control for it.
 * Anyone can change its state)
 *
 * rc - readers counter (current number of readers)
 * rc_mutex - mutex for procetion rc
 */


void writer() {
    down(db_access);
    /* ... write data to shared memory ... */
    up(db_access);
}

void reader() {
    lock(rc_mutex);
    rc++;
    if (rc == 1) {
        down(db_access);
    }
    unlock(rc_mutex);
    /* ... reading data from shared memory ... */
    lock(rc_mutex);
    rc--;
    if (rc == 0) {
        up(db_access);
    }
    unlock(rc_mutex);
}

// AND WHAT IF THERE ARE BILLIONS OF READERS? WHEN WE GONNA WRITE?

// lets add another mutex!

void writer() {
    lock(barrier); // lock barrier for readers
    down(db_access);
    /* ... write data to shared memory ... */
    up(db_access);
    unlock(barrier);
}

void reader() {
    lock(barrier); // barrier on enter. If someone writing right now then reader cant access shared data!
    unlock(barrier);
    lock(rc_mutex);
    rc++;
    if (rc == 1) {
        down(db_access);
    }
    unlock(rc_mutex);
    /* ... reading data from shared memory ... */
    lock(rc_mutex);
    rc--;
    if (rc == 0) {
        up(db_access);
    }
    unlock(rc_mutex);
}