#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

void qsort(int *a, int low, int high) {
    int i = low;
    int j = high;
    int x = a[(low + high) / 2];

    do {
        while (a[i] < x) ++i;
        while (a[j] > x) --j;
        if (i <= j) {
            std::swap(a[i], a[j]);
            ++i;
            --j;
        }
    } while (i <= j);

    if (low < j) qsort(a, low, j);
    if (i < high) qsort(a, i, high);
}

int main() {
	std::vector<int> a;
	int number = 0;

	while (scanf("%d", &number) == 1) {
		a.push_back(number);
	}

	qsort(&a[0], 0, a.size() - 1);

	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << std::endl;
	}

	return 0;
}
