#include <stdio.h>

int main(int argc, char *argv[]) {
    int a, b;

    scanf("%d %d", &a, &b);

    int c = 0;

    while (a >= b)
    {
        a -= b;
        c++;
    }

    printf("%d", c);

    return 0;
}
