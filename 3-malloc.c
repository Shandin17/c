#include <stdlib.h>
#include <math.h>

int main() {
    double *k;
    k = malloc(360*sizeof(double));
    for (int i = 0; i < 360; i ++) {
        k[i] = sin((2 * M_PI/ 360) * (double)i);
    }
    free(k);
    return 0;
}