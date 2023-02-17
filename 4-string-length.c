#include <stdio.h>

int string_length(const char* str) {
    int i;
    for (i = 0; str[i]; i++)
    {}
    return i;
}

void string_copy(char *dest, const char *src) {
    int i;
    for (i = 0; src[i]; i++) {
        dest[i] = src[i];
    }
    dest[i] = 0;
}

int main() {
    char* str = "abc";
    printf("string length: %d\n", string_length(str));
    return 0;
}