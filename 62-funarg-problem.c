

void sumprod(int *vec, int n, int *sum, int *prod) {
    int accum;
    int plus(int a) {
        return accum + a;
    }
    int times(int a) {
        return accum * a;
    }
    void reduce(int *vec, int len, int (*op)(int)) {
        if (!len) {
            return;
        }
        accum = op(*vec);
        reduce(vec + 1, len -1, op);
    }
    accum = 0;
    reduce(vec, n, &plus);
    *sum = accum;
    accum = 1;
    reduce(vec, n, &times);
    *prod = accum;
}