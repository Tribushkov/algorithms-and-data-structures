#include <stdio.h>
#include <string.h>
#include "malloc.h"

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

void HeapifyMin(int *a, size_t size, size_t i) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t min = i;

    if (left < size && a[left] < a[i]) {
        min = left;
    }

    if (right < size && a[right] < a[min]) {
        min = right;
    }

    if (min != i) {
        int buf = a[i];
        a[i] = a[min];
        a[min] = buf;

        HeapifyMin(a, size, min);
    }
}

void BuildHeap(int *a, size_t size) {
    for (size_t i = size / 2; i > 0; --i) {
        Heapify(a, size, i - 1);
    }
}

void BuildHeapMin(int *a, size_t size) {
    for (size_t i = size / 2; i > 0; --i) {
        HeapifyMin(a, size, i - 1);
    }
}

size_t CountTime(int *a, size_t n) {
    size_t sum = 0;

    while (n > 1) {
        size_t min = 1;

        if (n > 2 && a[2] < a[min]) min = 2;

        a[0] += a[min];
        sum += a[0];
        a[min] = a[n - 1];

        n--;

        HeapifyMin(a, n, min);
        HeapifyMin(a, n, 0);

    }

    return sum;
}

int main() {
    size_t n;

    scanf("%u", (unsigned *)&n);

    int *a = (int *)malloc(sizeof(int) * n);

    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    BuildHeapMin(a, n);

    size_t time = CountTime(a, n);

    printf("%u", (unsigned)time);

    return 0;
}
