#include <stdio.h>
#include "../library/Library.h"

int main() {
    printf("C: Starting application\n");

    char key[100] = "hello";
    char value[100];
    int ret = 0;

    ret = kv739_get(key, value);
    return 0;
}
