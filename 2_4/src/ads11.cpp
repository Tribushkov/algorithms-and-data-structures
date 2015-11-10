#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

void print(int *a, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}

	printf("\n");
}

size_t qsort_partition_forward(int *a, size_t n, size_t k) {
	size_t i, j;

	std::swap(a[k], a[n - 1]);

	for (i = 0, j = 0; j < n - 1; ++j) {
		if (a[j] <= a[n - 1]) {
			std::swap(a[i], a[j]);
			++i;
		}
	}

	std::swap(a[i], a[n - 1]);

	return i;
}

size_t qsort_partition_backward(int *a, size_t n, size_t k) {
	size_t i, j;

	std::swap(a[k], a[0]);

	for (i = n - 1, j = n - 1; j > 0; --j) {
		if (a[j] > a[0] || (a[j] == a[0] && j % 2 == 0)) {
			std::swap(a[i], a[j]);
			--i;
		}
	}

	std::swap(a[i], a[0]);

	return i;
}

size_t kth_element_recursive(int *a, size_t n, size_t k) {
	srand(getpid());

	size_t pivot = qsort_partition_backward(a, n, rand() % n);

	if (pivot < k) {
		return pivot + 1 + kth_element_recursive(a + pivot + 1, n - (pivot + 1), k - (pivot + 1));
	} else if (pivot == k) {
		return pivot;
	} else {
		return kth_element_recursive(a, pivot, k);
	}
}

size_t kth_element(int *a, size_t n, size_t k) {
	srand(getpid());

	size_t pos = 0;
	size_t pivot;

	for (;;) {
		pivot = qsort_partition_backward(a, n, rand() % n);

		if (pivot < k) {
			pos += pivot + 1;
			a += pivot + 1;
			n -= pivot + 1;
			k -= pivot + 1;
		} else if (pivot == k) {
			pos += pivot;
			break;
		} else {
			n = pivot;
		}
	}

	return pos;
}

int main() {
	size_t n, k;

	scanf("%u %u", (unsigned *)&n, (unsigned *)&k);

	int *a = new int[n];

	for (size_t i = 0; i < n; ++i) {
		scanf("%u", &a[i]);
	}

	printf("%u", a[kth_element(a, n, k)]);

	return 0;
};
