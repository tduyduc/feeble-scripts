// Emulates "cat" program without parameters, and outputs number of bytes read/written upon exit
#include <stdio.h>
int main() {
    unsigned long long i = 0;
    for (int c; (c = getchar()) != -1; i++) fputc(c, stdout);
    fprintf(stderr, "Bytes read: %llu\n", i);
    return 0;
}
