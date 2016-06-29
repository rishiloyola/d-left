#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "hash.c"

int main(int argc, char const *argv[])
{
    struct Table T1;
    init(&T1);
    bool output;
    for (int i = 0; i < 10; i++) {
        output = inserting(i, &T1);
    }
    output = delete(5, &T1);
    output = delete(1, &T1);
    output = lookup(5, &T1);
    return 0;
}
