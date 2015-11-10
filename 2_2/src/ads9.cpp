#include <iostream>
#include <cstdio>

struct get_column_t {
	int column;
	get_column_t(int _column) : column(_column) { }
	int operator ()(const int *data) { return data[column]; }
};

template<typename T, typename less_t>
void selection_sort(T *a, size_t rows, less_t &_get_digit) {
	for (size_t i = 0; i < rows - 1; ++i) {
		size_t min = i;

		for (size_t j = i + 1; j < rows; ++j) {
			if (_get_digit(a[j]) < _get_digit(a[min])) min = j;



		int *buf = a[i];

		a[i] = a[min];
		a[min] = buf;
	}
}

int main() {
	size_t n;

	scanf("%u", (unsigned *)&n);

	int **a = new int*[n];

	for (size_t i = 0; i < n; ++i) {
		a[i] = new int[4];
		a[i][3] = i;

		scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
	}

	for (size_t i = 0; i < 3; ++i) {
		get_column_t get_column(i);

		selection_sort<int *, get_column_t>(a, n, get_column);
	}

	for (size_t i = 0; i < n; ++i) {
		printf("%d ", a[i][3]);
    }

	return 0;
}
