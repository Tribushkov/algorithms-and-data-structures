#include <iostream>
#include <cstdio>
#include <list>

void Heapify(std::list<int> **a, size_t size, size_t i) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t min = i;

    if (left < size && a[left]->front() < a[i]->front()) {
    	min = left;
    }

    if (right < size && a[right]->front() < a[min]->front()) {
    	min = right;
    }

    if (min != i) {
    	std::swap(a[i], a[min]);

    	Heapify(a, size, min);
    }
}

void BuildHeap(std::list<int> **a, size_t size) {
    for (size_t i = size / 2; i > 0; --i) {
    	Heapify(a, size, i - 1);
    }
}

int main() {
	size_t n, k;

	std::cin >> n;
	std::cin >> k;

	std::list<int> **a = new std::list<int>*[k];

	for (size_t i = 0; i < n; ++i) {
		if (i < k) {
			a[i] = new std::list<int>();
		}

		int value;

		std::cin >> value;

		a[i % k]->push_back(value);
	}

	BuildHeap(a, k);

	for (;;) {
		std::cout << a[0]->front() << " ";

		a[0]->pop_front();

		if (a[0]->size() == 0) {
			a[0] = a[k - 1];
			--k;
		}

		if (k == 0) {
			break;
		}

		Heapify(a, k, 0);
	}

	return 0;
}
