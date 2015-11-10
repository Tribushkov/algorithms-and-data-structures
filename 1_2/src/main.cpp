#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n;

    scanf("%d", &n);

    int max_delimeter = 1;

    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0 && i > max_delimeter) {
            max_delimeter = i;
        }
    }

    int a = max_delimeter;
    int b = n - a;

    printf("%d %d", a, b);

    return 0;
}
