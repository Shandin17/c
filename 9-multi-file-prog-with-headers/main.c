#include "mod.h"

// gcc -Wall -g -c mod.c
// gcc -Wall -g -c main.c
// gcc main.c mod.c -o prog
// OR:
// gcc -Wall -g -c mod.c
// gcc -Wall -g main.c mod.o -o prog
// OR:
// gcc -Wall -g main.c mod.c -0 prog
int main() {
    hello_world();
    return 0;
}