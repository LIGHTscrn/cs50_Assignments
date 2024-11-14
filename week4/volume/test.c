#include <stdio.h>

int main(void)
{
    int p = 50;
    int *n = &p;
    printf("%i\n", *n);
    int x = 50 * *n;
    printf("%i\n", x);
}
