#include <unistd.h>
#include <errno.h>
#include <stdlib.h>



int main() {
    int fd[2];
    int p1, p2;
    pipe(fd);
    p1 = fork();
    if (p1 == 0) { // child #1 - only writing
        close(fd[0]);
        /* .... */
        write(fd[1], /* .... */);
        /* .... */
        exit(0);
    }
    p2 = fork();
    if (p2 == 0) { //child #2 - only reading
        close(fd[1]);
        /* .... */
        rc = read(fd[0], /* .... */);
        /* .... */
        exit(0);
    }
    // parent
    close(fd[0]);
    close(fd[1]);
    /* ...... */
}