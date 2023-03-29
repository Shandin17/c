// pseudocode

// n = 0, 1, 2, 3, 4
int left(int n) {
    return (n + 4 % 5);
}

int right(int n) {
    return (n + 1 % 5);
}
// assume that number of left fork is coincide with philosopher number
// fork == mutex

// WITHOUT DEADLOCK PROTECTION
void philosopher(int n) {
    for (;;) {
        think();
        lock(forks[n]); /* ! here all philosophers can bee locked all together (deadlock) ! */
        lock(forks[right(n)]);
        eat();
        unlock(forks[n]);
        unlock(forks[right(n)]);
    }
}

// WITH DEADLOCK PROTECTION
// possible solutions:

/**
 * 1. Semaphore
 */
void philosopher(int n) {
    for (;;) {
        think();
        down(sem);
        lock(forks[n]);
        lock(forks[right(n)]);
        eat();
        unlock(forks[n]);
        unlock(forks[right(n)]);
        up(sem);
    }
}
/**
 * Which init number should we choose for semaphore?? Max is 4, min is 1. But all have cons
 */


/** 2. Resource hierarchy
 Assume that all philosophers first take the fork with highest closest number (1 -> 1, 2 -> 2, .. , 4 -> 4)
 than one of them will be left handed (One that sits between 4 and 0) and others right handed
 What if there are several concurrency resources? (database)
 */


/** 3. Steward (additional mutex)
 */
void philosopher(int n) {
    for (;;) {
        think();
        lock(steward);
        lock(forks[n]);
        lock(forks[right(n)]);
        unlock(steward);
        eat();
        unlock(forks[n]);
        unlock(forks[right(n)]);
    }
}
/**
 * but what if one philosopher is eating and another one (closest to him) want to eat too??
 * than he asks steward for a fork. BUT another fork is busy! so steward stands behind this
 * philosopher til first one will finish his dish. AND ALL OTHER PHILOSOPHERS WILL WAIT TOO.
 * This can be solved by putting one fork back on the table after several tries (random) of catching resource
 *
 */




