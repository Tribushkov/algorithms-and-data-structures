#include <stdio.h>
#include <stdlib.h>

int findMissing(int *a, int n) {
    int a_n = n;
    int sum = 0;

    for (int i = 0; i < n; i++) {
        if (a_n == -1 || a_n < a[i]) {
            a_n = a[i];
        }

        sum += a[i];
    }

    int sum_theoratical = (0 + a_n) * (n + 1) / 2;

    return sum_theoratical - sum;
}

int main(int argc, char *argv[]) {
    int n;

    scanf("%d", &n);

    int *a = (int *)malloc(sizeof(n) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("%d", findMissing(a, n));

    return 0;
}
