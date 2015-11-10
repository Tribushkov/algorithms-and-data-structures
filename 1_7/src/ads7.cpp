#include <stdio.h>
#include <string.h>

void Heapify(int *a, size_t size, size_t i) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t largest = i;

    if (left < size && a[left] > a[i]) {
        largest = left;
    }

    if (right < size && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        int buf = a[i];
        a[i] = a[largest];
        a[largest] = buf;

        Heapify(a, size, largest);
    }
}

void BuildHeap(int *a, size_t size) {
    for (size_t i = size / 2; i > 0; --i) {
        Heapify(a, size, i - 1);
    }
}

void SortHeap(int *a, size_t size) {
    size_t n = size;

    for (size_t i = 0; i < size; ++i) {
        int buf = a[0];
        a[0] = a[n - 1];
        a[n - 1] = buf;

        Heapify(a, --n, 0);
    }
}

size_t CountTime(int *a, size_t n) {
    size_t overall_sum = 0;

    size_t prev_sum = a[0];

    for (size_t i = 1; i <= n / 2; ++i) {
        printf("%u ", (unsigned)overall_sum);
        overall_sum += a[i] + prev_sum;
        prev_sum =  a[i] + prev_sum;
    }

    prev_sum = a[n - 1];

    for (size_t i = n - 2; i >= n / 2 + 1; --i) {
        printf("%u ", (unsigned)overall_sum);
        overall_sum += a[i] + prev_sum;
        prev_sum =  a[i] + prev_sum;
    }

    return overall_sum;
}

int main() {
    size_t n;

    scanf("%u", (unsigned *)&n);

    int *a = new int[n];

    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    BuildHeap(a, n);
    SortHeap(a, n);

    printf("result=%u", (unsigned)CountTime(a, n));

    return 0;
}
