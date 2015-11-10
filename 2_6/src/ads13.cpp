#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>

const int abc_size = 256;

struct get_char_t {
	int k;
	get_char_t(int _k) : k(_k) { }
	int operator ()(const char *data) { return data[k]; }
};

template <typename T, typename less_t>
void counting_sort(T *a, int n, less_t &_get_digit, int *cnt) {
	for (int i = 0; i < abc_size; ++i) {
		cnt[i] = 0;
	}

	for (int i = 0; i < n; ++i) {
		++cnt[_get_digit(a[i])];
	}

	int sum = 0;
	for (int i = 0; i < abc_size; ++i) {
		int tmp = cnt[i];
		cnt[i] = sum;
		sum += tmp;
	}

	T *res = new T[n];

	for (int i = 0; i < n; ++i) {
		res[cnt[_get_digit(a[i])]] = a[i];
		++cnt[_get_digit(a[i])];
	}

	memcpy(a, res, n * sizeof(T));

	delete[] res;
}

void msd(char **a, int n, int k = 0) {
	int *groups = new int[abc_size + 1];

	groups[abc_size] = n;

	get_char_t get_char(k);

	counting_sort<char *, get_char_t>(a, n, get_char, groups);

	for (int i = 0; i < abc_size; ++i) {
		int group_size = groups[i + 1] - groups[i];
		if (group_size > 1) {
			msd(&a[groups[i]], group_size, k + 1);
		}
	}

	delete[] groups;
}

int main() {
	std::vector<char *> a;

	for (;;) {
		std::string str;
		std::getline(std::cin, str);

		if (str.empty()) {
			break;
		}

		char *c_str = new char[str.length() + 1];
		strcpy(c_str, str.c_str());

		a.push_back(c_str);
	}

	msd(&a[0], a.size());

	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << std::endl;
	}

	return 0;
}
