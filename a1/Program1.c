/* CS261- HW1 - Program1.c*/
/* Name: Kevin Pfeil
 * Date: 1/13/2020
 * Solution Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c) {
    *a += 1;
    *b -= 1;

    c = (*a - *b);

    return c;
}

int main() {
    srand(time(0));

    int x = rand() % 10;
    int y = rand() % 10;
    int z = rand() % 10;

    printf("x = %d, y = %d, z = %d\n", x, y, z);

    int val = foo(&x, &y, z);

    printf("After calling foo, x = %d, y = %d, z = %d\n", x, y, z);
    printf("Value returned by foo = %d and z = %d\n", val, z);

    return 0;
}