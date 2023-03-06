#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

enum { listen_queue_len = 16 };
int ls, ok;
struct sockaddr_in addr; // socket address

// 0 - protocol
// Specifying a protocol of 0 causes socket()
// to use an unspecified default protocol appropriate
// for the requested socket type.
ls = socket(AF_INET, SOCK_STREAM, 0);
if (ls == -1) {
    /* ... error code ... */
}
addr.sin_family = AF_INET;
addr.sin_port = htons(port); // host to network short
addr.sin_addr.s_addr = htonl(INADDR_ANY);
ok = bind(ls, &addr, sizeof(addr)); // bind network address to socket
if (ok == -1) {
    /* ... error code ... */
}

listen(ls, listen_queue_len); // listen mode
for (;;) {
    int cls, pid;
    socklen_t slen = sizeof(addr);
    cls = accept(ls, &addr, &slen);
    pid = fork();
    if (pid == 0) {
        close(ls);
        /**
         * working with client throught socket cls
         * Client came from address that now stored in addr structure
         */
        exit(0);
    }

    /* parent process */
    close(cls);

    /**
     * check whether successor process has finished working.
     * (killing zombies)
     */
    do {
        pid = wait4(-1, NULL, WHOHANG, NULL);
    } while (pid > 0);
}